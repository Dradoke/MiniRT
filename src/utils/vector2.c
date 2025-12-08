/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Calculates cross product of two 3D vectors
/// @param v1 
/// @param v2 
/// @return 
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		}});
}

/// @brief Calculates square length of a 3D vector
/// @note Faster than vec3_length
/// @param v 
/// @return 
t_f32	vec3_length_sq(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

/// @brief Calculates the length of a 3D vector
/// @param v 
/// @return 
t_f32	vec3_length(t_vec3 v)
{
	return (sqrtf(vec3_length_sq(v)));
}

/// @brief Normalizes a 3D vector
/// @param v 
/// @return 
t_vec3	vec3_normalize(t_vec3 v)
{
	t_f32	len;

	len = vec3_length(v);
	if (len == 0.0f)
		return ((t_vec3){{0, 0, 0}});
	return (vec3_scale(v, 1.0f / len));
}

/// @brief Rotates a 3D vector around an axis
/// @note Uses Rodrigue's Rotation Formula
/// @param v 
/// @param axis 
/// @param angle 
/// @return 
t_vec3	vec3_rotate(t_vec3 v, t_vec3 axis, t_f32 angle)
{
	t_vec3	k;
	t_vec3	rotated;
	t_f32	cos_a;
	t_f32	sin_a;

	k = vec3_normalize(axis);
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	rotated = vec3_add(vec3_scale(v, cos_a),
			vec3_scale(vec3_cross(k, v), sin_a));
	rotated = vec3_add(rotated,
			vec3_scale(k, vec3_dot(k, v) * (1.0f - cos_a)));
	return (rotated);
}
