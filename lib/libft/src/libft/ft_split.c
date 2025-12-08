/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Counts the number of words in a string separated by a delimiter.
// Returns the count of words in the string 's' using char 'c' as delimiter.
static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

// Frees allocated memory for the split result.
// Releases memory for 'result' array up to 'words' elements.
static void	free_split(char **result, int words)
{
	while (words >= 0)
		free(result[words--]);
	free(result);
}

// Splits a string into an array of substrings using a delimiter.
// Creates array of strings by splitting 's' using char 'c' as delimiter.
// Returns array of strings or NULL if allocation fails.
char	**ft_split(const char *s, char c)
{
	char	**result;
	int		words;
	int		i;
	char	*start;

	result = ft_calloc(((words = count_words(s, c)) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	i = 0;
	while (*s && i < words)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			result[i] = ft_substr(start, 0, s - start);
			if (!result[i++])
				return (free_split(result, i - 1), NULL);
		}
		else
			s++;
	}
	return (result);
}
