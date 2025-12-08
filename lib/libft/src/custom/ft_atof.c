/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts a string to a t_f32.
// Skips whitespace, handles '+'/'-' signs, then parses digits.
// Returns the converted t_f32 value.
t_f32	ft_atof(const char *str)
{
	t_f32	result;
	t_f32	sign;
	t_f32	divisor;

	result = 0;
	sign = 1;
	divisor = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*(str++) - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*(str++) - '0');
		divisor *= 10;
	}
	return ((result / divisor) * sign);
}
