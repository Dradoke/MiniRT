#include "minirt.h"

/// @brief Make a vector in a tengant space where the normal "n" point towards the "top"
/// @param seed used to always get a real random number
/// @return A vector (t_vec3) that point towards the "top"
t_vec3	get_local_dir(unsigned int *seed)
{
	float	r1;
	float	r2;
	float	phi;
	t_vec3	d_local;

	r1 = ft_random_float(0, 1, seed);
	r2 = ft_random_float(0, 1, seed);
	phi = 2.0 * PI * r2;
	d_local.x = cos(phi) * sqrt(1 - r1);
	d_local.y = sinf(phi) * sqrt(1 - r1);
	d_local.z = sqrtf(r1);
	return (d_local);
}

t_vec3 get_world_dir(t_vec3 u, t_vec3 v, t_vec3 w, t_vec3 d_local)
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

t_vec3 get_rand_dir(t_hit_record hit, t_vec3 d_local)
{
	t_vec3	w;
	t_vec3	a;
	t_vec3	u;
	t_vec3	v;
	t_vec3	d_new;

	w = hit.n;
	if (fabsf(w.x) > 0.9)
		a = (t_vec3){{0, 1, 0}};
	else
		a = (t_vec3){{1, 0, 0}};
	u = ft_normalize(ft_cross(a, w));
	v = ft_cross(w, u);
	d_new = get_world_dir(u, v, w, d_local);
	return (d_new);
}

t_ray	ft_create_reb_ray(t_vec3 d_new, t_hit_record hit)
{
    t_vec3	origine_rebound;

    /* CORRECTION : Augmenter EPSILON pour éviter que le cylindre se fasse de l'ombre à lui-même */
    /* Utiliser 1e-2 ou 1e-3 au lieu de EPSILON (1e-4) si nécessaire */
    origine_rebound = ft_vec3_add(hit.p, ft_vec3_scale(hit.n, 0.01f));
    return ((t_ray){origine_rebound, d_new});
}

t_rgba ft_calc_direct_light(t_hit_record hit, t_scene scene)
{
    int i = 0;
    float acc_r = 0.0f, acc_g = 0.0f, acc_b = 0.0f;
    t_vec3 light_dir;
    float cos_factor;
    t_ray shadow_ray;
    t_hit_record tmp_hit;

    /* object albedo in 0..1 */
    float albedo_r = (float)hit.color.r / 255.0f;
    float albedo_g = (float)hit.color.g / 255.0f;
    float albedo_b = (float)hit.color.b / 255.0f;

    while (i < scene.obj_count[LIGHT])
    {
        light_dir = get_dir(hit.p, scene.light[i].location);
        cos_factor = ft_get_scalaire(hit.n, light_dir);
        if (cos_factor <= 0.0f) { i++; continue; }

        shadow_ray = ft_create_reb_ray(light_dir, hit);
        
        /* Ajout d'un debug temporaire si tu veux vérifier la couleur brute sans lumière */
        // if (i == 0) return hit.color; 

        if (!hit_world(&shadow_ray, &scene, &tmp_hit) ||
            ft_vec3_len(ft_vec3_sub(tmp_hit.p, hit.p)) > get_dist(hit.p, scene.light[i].location))
        {
            /* light color and brightness in 0..1 */
            float lr = (float)scene.light[i].color.r / 255.0f * scene.light[i].brightness;
            float lg = (float)scene.light[i].color.g / 255.0f * scene.light[i].brightness;
            float lb = (float)scene.light[i].color.b / 255.0f * scene.light[i].brightness;

            /* diffuse = albedo * light * cos */
            acc_r += albedo_r * lr * cos_factor;
            acc_g += albedo_g * lg * cos_factor;
            acc_b += albedo_b * lb * cos_factor;
        }
        i++;
    }

    /* add ambient (ambient.color * ambient.brightness * albedo) */
    acc_r += ((float)scene.ambient_light.color.r / 255.0f) * scene.ambient_light.brightness * albedo_r;
    acc_g += ((float)scene.ambient_light.color.g / 255.0f) * scene.ambient_light.brightness * albedo_g;
    acc_b += ((float)scene.ambient_light.color.b / 255.0f) * scene.ambient_light.brightness * albedo_b;

    /* clamp and convert back to uint8 */
    t_rgba out;
    out.r = (uint8_t)(fminf(fmaxf(acc_r, 0.0f), 1.0f) * 255.0f);
    out.g = (uint8_t)(fminf(fmaxf(acc_g, 0.0f), 1.0f) * 255.0f);
    out.b = (uint8_t)(fminf(fmaxf(acc_b, 0.0f), 1.0f) * 255.0f);
    out.a = 255;
    return out;
}

t_rgba	trace_path(t_ray ray, t_scene scene, int depth)
{
    t_path_tracing	data;

    if (depth <= 0)
        return (t_rgba){{0, 0, 0, 0}};
    if (!hit_world(&ray, &scene, &data.hit))
        return (scene.ambient_light.color);


    if (scene.obj_count[LIGHT] > 0)
    {
        t_vec3 ld = get_dir(data.hit.p, scene.light[0].location);
        ft_get_scalaire(data.hit.n, ld);
    }

    /* REINTERPRETATION : Debug Normales avec Sécurité */
    /* Si l'objet n'a pas de couleur (noir), on affiche les Normales DEBUG */
    if (data.hit.color.r == 0 && data.hit.color.g == 0 && data.hit.color.b == 0)
    {
        t_rgba debug_n;
        t_vec3 n = data.hit.n;

        // 1. FORCER LA NORMALISATION (Correction du bug visuel "bruit")
        float len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
        if (len > 0.00001f)
        {
            n.x /= len;
            n.y /= len;
            n.z /= len;
        }

        // 2. Mapping [-1, 1] -> [0, 255]
        debug_n.r = (unsigned char)((n.x + 1.0f) * 0.5f * 255.0f);
        debug_n.g = (unsigned char)((n.y + 1.0f) * 0.5f * 255.0f);
        debug_n.b = (unsigned char)((n.z + 1.0f) * 0.5f * 255.0f);
        debug_n.a = 255;
        return (debug_n);
    }

    /* direct en float */
    t_rgb direct_rgb = {0.0f, 0.0f, 0.0f};
    {
        t_rgba direct = ft_calc_direct_light(data.hit, scene);
        direct_rgb = rgba_to_rgb(direct);
    }

    /* indirect : calcule entrant (récurse) en t_rgba, convertir en float et multiplier par albédo float */
    data.d_local = get_local_dir(&scene.seed);
    data.d_new = get_rand_dir(data.hit, data.d_local);
    data.next_ray = ft_create_reb_ray(data.d_new, data.hit);
    t_rgba entrant = trace_path(data.next_ray, scene, depth - 1);

    t_rgb entrant_rgb = rgba_to_rgb(entrant);
    t_rgb albedo_rgb = rgba_to_rgb(data.hit.color);
    t_rgb indirect_rgb = rgb_mult_rgb(entrant_rgb, albedo_rgb);

    /* somme en float */
    t_rgb out_rgb = rgb_add(direct_rgb, indirect_rgb);

    /* convertir et retourner */
    return (rgb_to_rgba(out_rgb));
}
