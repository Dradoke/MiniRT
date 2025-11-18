#include "minirt.h"

/// @brief Make a vector in a tengant space where the normal "n" point towards the "top"
/// @param seed used to always get a real random number
/// @return A vector (t_vec3) that point towards the "top"
t_vec3	const get_local_dir(unsigned int *seed)
{
	float	r1;
	float	r2;
	float	phi;
	t_vec3	d_local;

	r1 = ft_random_float(0, 1, &seed);
	phi = 2.0 * PI * r2;
	d_local.x = cos(phi) * sqrt(1 - r1);
	d_local.y = sinf(phi) * sqrt(1 - r1);
	d_local.z = sqrtf(r1);
	return (d_local);
}

t_vec3 const get_world_dir(t_vec3 u, t_vec3 v, t_vec3 w, t_vec3 d_local)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;
	t_vec3	direction_unnormalized;

	term1 = ft_vec3_scale(u, d_local.x);
	term2 = ft_vec3_scale(v, d_local.y);
	term3 = ft_vec3_scale(w, d_local.z);
	direction_unnormalized = ft_vec3_add(ft_vec3_add(term1, term2), term3);
	return (ft_normalize(direction_unnormalized));
}

t_vec3 const	get_rand_dir(t_hit_record hit, t_vec3 d_local)
{
	t_vec3	w;
	t_vec3	a;
	t_vec3	u;
	t_vec3	v;
	t_vec3	d_new;

	w = hit.n;
	if (fabsf(w.x) > 0.9)
		a = (t_vec3){0, 1, 0};
	else
		a = (t_vec3){1, 0, 0};
	u = ft_normalize(ft_cross(a, w));
	v = ft_cross(w, u);
	d_new = get_world_dir(u, v, w, d_local);
}

t_rgba const	ft_calc_direct_light(t_hit_record hit, t_scene scene)
{
	int	i;
	t_rgba	direct_light;
	t_vec3	light_dir;
	float	cos_factor;
	t_ray	new_ray;

	i = 0;
	while (i < scene.obj_count[LIGHT])
	{
		light_dir = get_dir(hit.p, scene.light[i].location);
		cos_factor = get_scalaire(hit.p, light_dir);
		if (cos_factor <= 0)
			i++;
		else
		{
			new_ray = (t_ray){ft_vec3_add(hit.p,
				ft_vec3_scale(hit.n, EPSILON)), light_dir};
			// Lancer le rayon, si l'objet touche n'est pas une lumiere, on incremente et next light
		}
	}
	
}

t_ray	ft_create_reb_ray(t_vec3 d_new, t_hit_record hit)
{
	t_vec3	origine_rebound;

	origine_rebound = ft_vec3_add(hit.p, ft_vec3_scale(hit.n, EPSILON));
	return ((t_ray){origine_rebound, d_new});
}

t_rgba	trace_path(t_ray ray, t_scene scene, int depth)
{
	t_path_tracing	data;
	static unsigned int	seed;

	if (depth <= 0)
		return (t_rgba){0, 0, 0, 0};
	// data.hit = trouver_intersection(rayon, scene);
	if (data.hit.has_touched == FALSE)
		return (scene.ambient_light.color);
	data.direct_light = ft_calc_direct_light(data.hit, scene);
	ft_init_random_seed(&seed);
	data.d_new = get_rand_dir(data.hit, get_local_dir(&seed));
	data.next_ray = ft_create_reb_ray(data.d_new, data.hit);
	data.entrant_light = trace_path(data.next_ray, scene, depth - 1);
	data.indirect_light = ft_rgba_mult(data.entrant_light, data.hit.color);
	data.out_light = ft_rgba_add(data.direct_light, data.indirect_light);
	return (data.out_light);
}
