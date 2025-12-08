/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Make a vector in a tengant space where the normal
/// @brief "n" point towards the "top"
/// @param seed used to always get a real random number
/// @return A vector (t_vec3) that point towards the "top"
t_vec3	get_local_dir(unsigned int *seed)
{
	float	r1;
	float	r2;
	float	phi;
	t_vec3	d_local;

	r1 = ft_random_float(RANDF_MIN, RANDF_MAX, seed);
	r2 = ft_random_float(RANDF_MIN, RANDF_MAX, seed);
	phi = 2.0 * PI * r2;
	d_local.x = cos(phi) * sqrt(1 - r1);
	d_local.y = sinf(phi) * sqrt(1 - r1);
	d_local.z = sqrtf(r1);
	return (d_local);
}

/// @brief Transforms a direction from local tangent space to world space
/// @param u Tangent vector
/// @param v Bitangent vector
/// @param w Normal vector
/// @param d_local Direction in local space
/// @return Direction in world space
t_vec3	get_world_dir(t_vec3 u, t_vec3 v, t_vec3 w, t_vec3 d_local)
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

/// @brief Generates a random direction in the hemisphere oriented by the normal
/// @param hit The hit record containing the normal
/// @param d_local Random direction in local space
/// @return Random direction in world space
t_vec3	get_rand_dir(t_hit_record hit, t_vec3 d_local)
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

/// @brief Creates a rebound ray slightly offset from the surface to avoid acne
/// @param d_new The new ray direction
/// @param hit The hit record containing the origin
/// @return The new ray
t_ray	ft_create_reb_ray(t_vec3 d_new, t_hit_record hit)
{
	t_vec3	origine_rebound;

	origine_rebound = ft_vec3_add(hit.p, ft_vec3_scale(hit.n, 0.01f));
	return ((t_ray){origine_rebound, d_new});
}

/// @brief Converts RGBA color (0-255) to RGB float (0.0-1.0)
/// @param color The RGBA color
/// @return The RGB float color
t_rgb	get_albedo(t_rgba color)
{
	t_rgb	albedo;

	albedo.r = (float)color.r / 255.0f;
	albedo.g = (float)color.g / 255.0f;
	albedo.b = (float)color.b / 255.0f;
	return (albedo);
}
