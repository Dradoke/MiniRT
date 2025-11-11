/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
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
