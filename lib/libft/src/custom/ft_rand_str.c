/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Generates a random string of uppercase letters (A-Z) with specified length.
// Uses /dev/urandom to get random bytes, mapping each byte to a letter.
// Returns a malloc'd string that must be freed by the caller when done.
char	*ft_rand_str(size_t len)
{
	int				fd;
	unsigned char	*str;

	fd = open("/dev/urandom", O_RDONLY);
	str = ft_calloc(len + 1);
	if (!str)
		return (NULL);
	if (fd >= 0)
		read(fd, str, len);
	close(fd);
	str[len] = '\0';
	while (len--)
		str[len] = 'A' + (str[len] % 26);
	return ((char *)str);
}
