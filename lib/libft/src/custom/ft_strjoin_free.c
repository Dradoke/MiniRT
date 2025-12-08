/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Concatenates two strings into a new string.
// Allocates and creates a new string by joining 's1' and 's2'.
// Returns the new string or NULL if allocation fails.
// Free the two strings passed in parameter
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	total_len;

	s1_len = ft_strlen(s1) + 1;
	total_len = ft_strlen(s2) + s1_len;
	new_str = (char *)malloc(total_len * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len);
	ft_strlcat(new_str, s2, total_len);
	free(s1);
	free(s2);
	return (new_str);
}
