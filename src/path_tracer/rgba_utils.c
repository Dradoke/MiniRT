/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Converts RGBA (0-255) to RGB float (0.0-1.0)
/// @param c The RGBA color
/// @return The RGB float color
t_rgb	rgba_to_rgb(t_rgba c)
{
	t_rgb	out;

	out.r = (float)c.r / 255.0f;
	out.g = (float)c.g / 255.0f;
	out.b = (float)c.b / 255.0f;
	return (out);
}

/// @brief Converts RGB float (0.0-1.0) to RGBA (0-255)
/// @param c The RGB float color
/// @return The RGBA color
t_rgba	rgb_to_rgba(t_rgb c)
{
	t_rgba	out;

	out.r = (uint8_t)(fminf(fmaxf(c.r, 0.0f), 1.0f) * 255.0f);
	out.g = (uint8_t)(fminf(fmaxf(c.g, 0.0f), 1.0f) * 255.0f);
	out.b = (uint8_t)(fminf(fmaxf(c.b, 0.0f), 1.0f) * 255.0f);
	out.a = 255;
	return (out);
}

/// @brief Multiplies two RGB float colors component-wise
/// @param a First color
/// @param b Second color
/// @return The product of the colors
t_rgb	rgb_mult_rgb(t_rgb a, t_rgb b)
{
	t_rgb	r;

	r.r = a.r * b.r;
	r.g = a.g * b.g;
	r.b = a.b * b.b;
	return (r);
}

/// @brief Adds two RGB float colors component-wise
/// @param a First color
/// @param b Second color
/// @return The sum of the colors
t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	t_rgb	r;

	r.r = a.r + b.r;
	r.g = a.g + b.g;
	r.b = a.b + b.b;
	return (r);
}

/// @brief Multiplies two RGBA colors by converting to float and back
/// @param c1 First color
/// @param c2 Second color
/// @return The product of the colors
t_rgba	ft_rgba_mult(t_rgba c1, t_rgba c2)
{
	t_rgb	a;
	t_rgb	b;
	t_rgb	r;

	a = rgba_to_rgb(c1);
	b = rgba_to_rgb(c2);
	r = rgb_mult_rgb(a, b);
	return (rgb_to_rgba(r));
}
