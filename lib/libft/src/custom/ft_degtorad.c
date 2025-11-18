/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_degtorad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
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
