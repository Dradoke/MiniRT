/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd_cspct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfd.h"

// Prints a single character to standard output.
// Writes character 'c' using the write system call.
// Returns 1 (number of characters printed).
int	ft_printchar(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

// Outputs a string to standard output.
// Writes each character in 'str' to stdout in sequence.
// Helper function with no return value.
void	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

// Prints a string to standard output.
// Handles NULL strings by printing "(null)".
// Returns the number of characters printed.
int	ft_printstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr(fd, "(null)");
		return (6);
	}
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

// Prints a percent sign to standard output.
// Handles the %% format specifier in ft_printf.
// Returns 1 (number of characters printed).
int	ft_printpct(int fd)
{
	write(fd, "%", 1);
	return (1);
}
