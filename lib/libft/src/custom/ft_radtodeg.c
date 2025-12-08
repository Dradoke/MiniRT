/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radtodeg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts radians to degrees.
// Multiplies radians by 180/pi for the conversion.
// Uses 3.14159265358979323846 as the value of pi.
t_f32	ft_radtodeg(t_f32 rad)
{
	t_f32		pi;
	t_f32		deg;

	pi = 3.14159265358979323846f;
	deg = rad * (180.0f / pi);
	return (deg);
}
