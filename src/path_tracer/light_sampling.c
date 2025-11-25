#include "minirt.h"

/// @brief 
/// @param pool 
/// @param new_s new_s is the new candidate
/// @param new_w new_w is the weight of new_s
void	update_pool(t_pool pool, t_sample new_s, float new_w, unsigned int seed)
{
	float	p_replace;

	pool.sum_weight += new_w;
	pool.nb_samples += 1;
	p_replace = new_w / pool.sum_weight;
	if (ft_random_float(0, 1, &seed) < p_replace)
		pool.sample = new_s;
}

/// @brief Calculate the RGB Flux of a Point Light
/// @param lights 
t_rgba	ft_flux_rgb_pl(t_point_light lights)
{
    const float k = 10.0f; /* ou autre échelle souhaitée */
    t_rgba	e;
    float rf = (lights.color.r / 255.0f) * k;
    float gf = (lights.color.g / 255.0f) * k;
    float bf = (lights.color.b / 255.0f) * k;
    /* clamp éventuel */
    e.r = (uint8_t)(fminf(rf, 1.0f) * 255.0f);
    e.g = (uint8_t)(fminf(gf, 1.0f) * 255.0f);
    e.b = (uint8_t)(fminf(bf, 1.0f) * 255.0f);
    e.a = 255;
    return (e);
}

/// @brief Calculate the RGB Flux of a Directional Light (Sun, Ambiant Light)
/// @param lights 
t_rgba	ft_flux_rgb_dl(t_ambiant_light lights)
{
	const float k = powf(10.0, 5);
	t_rgba	e;
	t_rgba	light_rgb;

	light_rgb = lights.color;
	e.r = light_rgb.r * k;
	e.g = light_rgb.g * k;
	e.b = light_rgb.b * k;
	return (e);
}

float	ft_luminance(t_rgba light_rgb)
{
	t_rgb	human_eye_factor;
	float	luminance;

	luminance = 0.0;
	human_eye_factor.r = 0.2126;
	human_eye_factor.g = 0.7152;
	human_eye_factor.b = 0.0722;
	luminance += light_rgb.r * human_eye_factor.r;
	luminance += light_rgb.g * human_eye_factor.g;
	luminance += light_rgb.b * human_eye_factor.b;
	return (luminance);
}

t_rgba	ft_init_rgb(void)
{
	t_rgba	rgba;

	rgba.r = 0;
	rgba.g = 0;
	rgba.b = 0;
	rgba.b = 1;
	return (rgba);
}

/// @brief Calculate the total Wheight of the scene lights
/// @param lights scene lights array
/// @return the total lighting wheight as a float
float	ft_scene_light_wheight(t_point_light *lights)
{
	float	total_wheight;
	t_rgba	light_energy;
	int		i;

	i = 0;
	total_wheight = 0.0;
	while (lights[i].brightness)
	{
		light_energy = ft_init_rgb();
		light_energy = ft_flux_rgb_pl(lights[i]);
		lights[i].brightness = ft_luminance(light_energy);
		total_wheight += lights[i].brightness;
		i++;
	}
	return (total_wheight);
}

float	ft_wheight_target(float total_wheight)
{
	unsigned int	seed;

	ft_init_random_seed(&seed);
	return (ft_random_float(RANDF_MIN, RANDF_MAX, seed) * total_wheight);
}
