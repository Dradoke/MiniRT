/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	is_in_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (TRUE);
		charset++;
	}
	return (FALSE);
}

static void	get_counts(const char *s, const char *charset,
	int *word_count, size_t *total_chars)
{
	t_bool	in_word;

	*word_count = 0;
	*total_chars = 0;
	in_word = FALSE;
	while (*s)
	{
		if (!is_in_charset(*s, charset))
		{
			if (!in_word)
			{
				in_word = TRUE;
				(*word_count)++;
			}
			(*total_chars)++;
		}
		else
			in_word = FALSE;
		s++;
	}
}

static void	process_char(char **result_ptr, const char *s_char,
	char **str_buf_ptr, t_bool *in_word)
{
	if (!*in_word)
	{
		*in_word = TRUE;
		*result_ptr = *str_buf_ptr;
	}
	**str_buf_ptr = *s_char;
	(*str_buf_ptr)++;
}

static void	populate_split(char **result, char *strings_buffer,
	const char *s, const char *charset)
{
	t_bool	in_word;
	int		i;

	i = 0;
	in_word = FALSE;
	while (*s)
	{
		if (!is_in_charset(*s, charset))
		{
			process_char(&result[i], s, &strings_buffer, &in_word);
			if (!(*s && !is_in_charset(*(s + 1), charset)))
				i++;
		}
		else
		{
			if (in_word)
			{
				in_word = FALSE;
				*strings_buffer++ = '\0';
			}
		}
		s++;
	}
	if (in_word)
		*strings_buffer = '\0';
}

/// @brief Splits a string by a set of characters, allocating a single
/// contiguous block of memory. The entire result can be freed with a single
/// call to free() on the returned pointer.
/// @param s The string to split.
/// @param charset A string containing all delimiter characters.
/// @return char **
/// @retval Success: A null-terminated array of strings
/// @retval Fail: NULL if allocation fails.
char	**ft_split_charset(const char *s, const char *charset)
{
	char	**result;
	char	*strings_buffer;
	int		word_count;
	size_t	total_chars;
	size_t	total_size;

	if (!s)
		return (NULL);
	get_counts(s, charset, &word_count, &total_chars);
	if (word_count == 0)
		return (ft_calloc(sizeof(char *)));
	total_size = (word_count + 1) * sizeof(char *) + total_chars + word_count;
	result = malloc(total_size);
	if (!result)
		return (NULL);
	strings_buffer = (char *)(result + word_count + 1);
	populate_split(result, strings_buffer, s, charset);
	result[word_count] = NULL;
	return (result);
}
