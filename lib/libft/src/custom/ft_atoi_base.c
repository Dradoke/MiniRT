/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Validates a base string for conversion.
// Checks for proper length and valid characters
// (no duplicates or special chars).
// Returns 1 if valid, 0 if invalid.
int	base_verif(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i + 1])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j]
				|| base[i] == '-' || base[i] == '+'
				|| base[j] == '-' || base[j] == '+'
				|| base[i] <= 32 || base[i] >= 127
				|| base[j] <= 32 || base[j] >= 127)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// Finds a character's position in a base string.
// Searches for character 'c' in the base and returns its position.
// Returns -1 if the character is not in the base.
int	char_is_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

// Converts a string to an integer using a specified base.
// Handles whitespace, signs, and converts digits according to custom base.
// Returns the converted integer or 0 if the base is invalid.
int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	sub0;
	int	nbr;
	int	len;

	if (!base_verif(base))
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	sub0 = 1;
	while (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sub0 *= -1;
	nbr = 0;
	len = ft_strlen(base);
	while (str[i])
	{
		if (char_is_base(str[i], base) < 0)
			return (0);
		nbr *= len;
		nbr += char_is_base(str[i++], base);
	}
	return (nbr * sub0);
}
