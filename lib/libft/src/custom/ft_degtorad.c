/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_degtorad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts degrees to radians.
// Multiplies degrees by pi/180 for the conversion.
// Uses 3.14159265358979323846 as the value of pi.
t_f32	ft_degtorad(t_f32 deg)
{
	t_f32		pi;
	t_f32		rad;

	pi = 3.14159265358979323846f;
	rad = deg * (pi / 180.0f);
	return (rad);
}
