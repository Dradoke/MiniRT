/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts a string to a t_f64.
// Skips whitespace, handles '+'/'-' signs, then parses digits.
// Returns the converted t_f64 value.
t_f64	ft_atod(const char *str)
{
	t_f64	result;
	t_f64	sign;
	t_f64	divisor;

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
