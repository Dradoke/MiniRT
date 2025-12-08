/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Zeroes a block of memory.
// Writes 'n' zero bytes to the string 's'.
// Uses ft_memset to set all bytes to zero.
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	if (!n)
		return ;
	i = 0;
	str = s;
	while (i < n)
		*(str + i++) = '\0';
}
