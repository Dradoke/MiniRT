/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *original, size_t size)
{
	size_t	i;
	char	*src;
	char	*dest;

	src = original;
	if (!src)
		return (ft_calloc(size));
	i = 0;
	dest = ft_calloc(size);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	free(src);
	return (dest);
}
