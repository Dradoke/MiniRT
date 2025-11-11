/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
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
