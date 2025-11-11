/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radtodeg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
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
