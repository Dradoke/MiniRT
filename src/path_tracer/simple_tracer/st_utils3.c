#include "minirt.h"

t_rgba	ft_calc_direct_light(t_hit_record hit, t_scene scene)
{
	int		i;
	t_rgb	acc;
	t_rgb	albedo;
	t_rgb	contrib;

	i = 0;
	acc = (t_rgb){0.0f, 0.0f, 0.0f};
	albedo = get_albedo(hit.color);
	while (i < scene.obj_count[LIGHT])
	{
		contrib = calc_light_contrib(hit, scene, i, albedo);
		acc.r += contrib.r;
		acc.g += contrib.g;
		acc.b += contrib.b;
		i++;
	}
	acc = add_ambient(acc, scene, albedo);
	return (rgb_to_rgba_clamped(acc));
}
