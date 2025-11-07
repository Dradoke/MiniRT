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


/// @brief Calculate the RGB Flux of an Area Light (Lantern, Candle, Floor Lamp, etc)
/// @param lights 
// void	ft_flux_rgb_al(t_list lights)
// {

// }

/// @brief Calculate the RGB Flux of a Point Light
/// @param lights 
t_rgb	ft_flux_rgb_pl(t_light lights)
{
	const float k = 10.0;
	t_rgb	e;
	t_rgb	light_rgb;
	
	light_rgb = lights.data.point_light.color;
	e.r = light_rgb.r * k;
	e.g = light_rgb.g * k;
	e.b = light_rgb.b * k;
	return (e);
}

/// @brief Calculate the RGB Flux of a Directional Light (Sun, Ambiant Light)
/// @param lights 
t_rgb	ft_flux_rgb_dl(t_light lights)
{
	const float k = powf(10.0, 5);
	t_rgb	e;
	t_rgb	light_rgb;

	light_rgb = lights.data.ambiant_light.color;
	e.r = light_rgb.r * k;
	e.g = light_rgb.g * k;
	e.b = light_rgb.b * k;
	return (e);
}

float	ft_luminance(t_rgb light_rgb)
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

t_rgb	ft_init_rgb(void)
{
	t_rgb	rgb;

	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	return (rgb);
}

/// @brief Calculate the total Wheight of the scene lights
/// @param lights array of the scene lights
/// @return the total lighting wheight as a float
float	ft_scene_light_wheight(t_light *lights)
{
	float	total_wheight;
	t_rgb	light_energy;
	int		i;

	i = 0;
	total_wheight = 0.0;
	while (lights[i].light_type)
	{
		light_energy = ft_init_rgb();
		if (lights[i].light_type == POINT_LIGHT)
		{
			light_energy = ft_flux_rgb_pl(lights[i]);
		}
		else if (lights[i].light_type == DIR_LIGHT)
		{
			light_energy = ft_flux_rgb_dl(lights[i]);
		}
		lights[i].light_energy = ft_luminance(light_energy);
		total_wheight += lights[i].light_energy;
		i++;
	}
	return (total_wheight);
}
