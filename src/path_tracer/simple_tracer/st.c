#include "minirt.h"

static void	trace_path_utils1(t_path_tracing *data, t_scene scene)
{
	(*data).d_local = get_local_dir(&scene.seed);
	(*data).d_new = get_rand_dir((*data).hit, (*data).d_local);
	(*data).next_ray = ft_create_reb_ray((*data).d_new, (*data).hit);
}

static void	trace_path_utils2(t_path_tracing *data)
{
	t_rgb	albedo_rgb;

	albedo_rgb = rgba_to_rgb((*data).hit.color);
	(*data).indirect_light = rgb_mult_rgb((*data).entrant_light, albedo_rgb);
	(*data).out_light = rgb_add((*data).direct_light, (*data).indirect_light);
}

t_rgba	path_trace(t_ray ray, t_scene scene, int depth)
{
	t_path_tracing	data;
	t_rgba			entrant;
	t_rgba			direct;
	t_vec3			ld;

	if (depth <= 0)
		return ((t_rgba){{0, 0, 0, 0}});
	if (!hit_world(&ray, &scene, &data.hit))
		return (scene.ambient_light.color);
	if (scene.obj_count[LIGHT] > 0)
	{
		ld = get_dir(data.hit.p, scene.light[0].location);
		ft_get_scalaire(data.hit.n, ld);
	}
	data.direct_light = (t_rgb){0.0f, 0.0f, 0.0f};
	{
		direct = ft_calc_direct_light(data.hit, scene);
		data.direct_light = rgba_to_rgb(direct);
	}
	trace_path_utils1(&data, scene);
	entrant = path_trace(data.next_ray, scene, depth - 1);
	data.entrant_light = rgba_to_rgb(entrant);
	trace_path_utils2(&data);
	return (rgb_to_rgba(data.out_light));
}

t_rgba	ray_trace(t_ray ray, t_scene scene, int depth)
{
	t_path_tracing	data;
	t_rgba			direct;

	if (depth <= 0)
		return ((t_rgba){{0, 0, 0, 0}});
	if (!hit_world(&ray, &scene, &data.hit))
		return (scene.ambient_light.color);
	direct = ft_calc_direct_light(data.hit, scene);
	return (direct);
}

t_rgba	trace_ray(t_ray ray, t_scene scene, int depth, t_bool *flags)
{
	if (flags[REFLECT] == TRUE)
		return (path_trace(ray, scene, depth));
	return (ray_trace(ray, scene, depth));
}
