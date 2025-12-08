/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Calculates the scalar product (dot product) of two vectors
/// @brief Returns 0.0 if the result is negative (clamped)
/// @param vec1 First vector
/// @param vec2 Second vector
/// @return The scalar product or 0.0
float	ft_get_scalaire(t_vec3 vec1, t_vec3 vec2)
{
	float	scalaire;

	scalaire = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	if (scalaire <= 0.0)
		return (0.0);
	else
		return (scalaire);
}

/// @brief Negates a vector (inverts its direction)
/// @param v The vector to negate
/// @return A new vector with negated components
t_vec3	ft_vec3_neg(t_vec3 v)
{
	return ((t_vec3){{-v.x, -v.y, -v.z}});
}

/// @brief Calculates the dot product of two vectors
/// @param v1 First vector
/// @param v2 Second vector
/// @return The dot product value
double	ft_vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/// @brief Calculates the squared length of a vector
/// @brief Useful for distance comparisons without square root
/// @param v The vector
/// @return The squared length
double	ft_vec3_len2(t_vec3 v)
{
	return (ft_vec3_dot(v, v));
}

/// @brief Calculates the length (magnitude) of a vector
/// @param v The vector
/// @return The length
double	ft_vec3_len(t_vec3 v)
{
	return (sqrt(ft_vec3_len2(v)));
}
