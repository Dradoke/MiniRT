/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Applies brightness to the light's base color
/// @param light The point light source
/// @return The adjusted light color
t_rgb	get_light_color(t_point_light light)
{
	t_rgb	color;

	color.r = (float)light.color.r / 255.0f * light.brightness;
	color.g = (float)light.color.g / 255.0f * light.brightness;
	color.b = (float)light.color.b / 255.0f * light.brightness;
	return (color);
}

/// @brief Checks if a light source is visible from a hit point (Shadow ray)
/// @param hit The hit point
/// @param scene The scene
/// @param i Index of the light
/// @return 1 if visible, 0 if occluded
int	is_light_visible(t_hit_record hit, t_scene scene, int i)
{
	t_ray			shadow_ray;
	t_hit_record	tmp_hit;
	t_vec3			light_dir;
	float			hit_dist;

	light_dir = get_dir(hit.p, scene.light[i].location);
	shadow_ray = ft_create_reb_ray(light_dir, hit);
	if (!hit_world(&shadow_ray, &scene, &tmp_hit))
		return (1);
	hit_dist = ft_vec3_len(ft_vec3_sub(tmp_hit.p, hit.p));
	if (hit_dist > get_dist(hit.p, scene.light[i].location))
		return (1);
	return (0);
}

/// @brief Calculates the diffuse contribution of a single light
/// @param hit The hit point
/// @param scene The scene
/// @param i Index of the light
/// @param albedo The surface color
/// @return The calculated color contribution
t_rgb	calc_light_contrib(t_hit_record hit, t_scene scene, int i,
	t_rgb albedo)
{
	t_vec3	light_dir;
	float	cos_factor;
	t_rgb	light_color;
	t_rgb	contrib;

	light_dir = get_dir(hit.p, scene.light[i].location);
	cos_factor = ft_get_scalaire(hit.n, light_dir);
	if (cos_factor <= 0.0f || !is_light_visible(hit, scene, i))
		return ((t_rgb){0.0f, 0.0f, 0.0f});
	light_color = get_light_color(scene.light[i]);
	contrib.r = albedo.r * light_color.r * cos_factor;
	contrib.g = albedo.g * light_color.g * cos_factor;
	contrib.b = albedo.b * light_color.b * cos_factor;
	return (contrib);
}

/// @brief Adds the ambient light contribution to the accumulated color
/// @param acc The accumulated color so far
/// @param scene The scene containing ambient light settings
/// @param albedo The surface color
/// @return The new accumulated color
t_rgb	add_ambient(t_rgb acc, t_scene scene, t_rgb albedo)
{
	t_rgb	ambient;

	ambient.r = (float)scene.ambient_light.color.r / 255.0f;
	ambient.g = (float)scene.ambient_light.color.g / 255.0f;
	ambient.b = (float)scene.ambient_light.color.b / 255.0f;
	acc.r += ambient.r * scene.ambient_light.brightness * albedo.r;
	acc.g += ambient.g * scene.ambient_light.brightness * albedo.g;
	acc.b += ambient.b * scene.ambient_light.brightness * albedo.b;
	return (acc);
}

/// @brief Converts a float RGB color to a clamped byte RGBA color
/// @param color The float RGB color
/// @return The clamped RGBA color
t_rgba	rgb_to_rgba_clamped(t_rgb color)
{
	t_rgba	out;

	out.r = (uint8_t)(fminf(fmaxf(color.r, 0.0f), 1.0f) * 255.0f);
	out.g = (uint8_t)(fminf(fmaxf(color.g, 0.0f), 1.0f) * 255.0f);
	out.b = (uint8_t)(fminf(fmaxf(color.b, 0.0f), 1.0f) * 255.0f);
	out.a = 255;
	return (out);
}
