/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Allocates and zero-initializes a character array.
// Allocates 'size' bytes of memory and fills them with null bytes.
// Returns a pointer to the allocated memory or NULL if allocation fails.
char	*ft_calloc_char(size_t size)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(size);
	if (!new)
		return (NULL);
	while (i < size)
		new[i++] = '\0';
	return (new);
}

// Calculates length of a line and checks for newline character.
// Stores position of newline in nl[0] and sets nl[1] if newline was found.
// Returns the number of characters to read until newline or end of string.
int	linelen(char *str, int *nl)
{
	nl[0] = 0;
	nl[1] = 0;
	while (str[nl[0]])
	{
		if (str[nl[0]] == '\n')
			return (nl[1] = 1, ++nl[0]);
		nl[0]++;
	}
	return (nl[0]);
}

// Copies characters from buffer to line and shifts remaining buffer content.
// Copies until newline or end of buffer, then shifts remaining characters.
// Updates line index and zeroes out used buffer positions.
void	cpybuf(char *line, char *buf, size_t *li)
{
	int	bj;
	int	bi;

	bj = 0;
	bi = 0;
	while (buf[bj])
	{
		if (buf[bj] == '\n')
		{
			line[(*li)++] = buf[bj++];
			break ;
		}
		line[(*li)++] = buf[bj++];
	}
	while (buf[bj])
		buf[bi++] = buf[bj++];
	while (bi < bj)
		buf[bi++] = '\0';
}
