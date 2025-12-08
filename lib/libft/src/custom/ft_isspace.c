/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if character is a whitespace character.
// Tests for space, tab, vertical tab, form feed, carriage return.
// Returns 1 if TRUE, 0 if FALSE.
int	ft_isspace(char c)
{
	if (c == ' ' || ((c >= 9 && c <= 13) && c != '\n'))
		return (1);
	return (0);
}

// Checks if character is a whitespace or newline character.
// Tests for space, tab, newline, vertical tab, form feed, carriage return.
// Returns 1 if TRUE, 0 if FALSE.
int	ft_isspace_nl(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
