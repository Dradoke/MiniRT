/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfd.h"

// Processes format specifiers and routes to appropriate printing functions.
// Handles c,s,p,d,i,u,x,X,% specifiers using corresponding functions.
// Returns number of characters printed.
int	ft_formats(int fd, va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_printchar(fd, va_arg(args, int));
	else if (format == 's')
		len += ft_printstr(fd, va_arg(args, char *));
	else if (format == 'p')
		len += ft_print_ptr(fd, va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		len += ft_pn_b(fd, va_arg(args, int), "0123456789");
	else if (format == 'u')
		len += ft_pn_b(fd, va_arg(args, t_ui32), "0123456789");
	else if (format == 'x')
		len += ft_pn_b(fd, va_arg(args, t_ui32), "0123456789abcdef");
	else if (format == 'X')
		len += ft_pn_b(fd, va_arg(args, t_ui32), "0123456789ABCDEF");
	else if (format == '%')
		len += ft_printpct(fd);
	return (len);
}

// Printf implementation with variadic arguments support.
// Parses format string, processes specifiers with ft_formats.
// Write in the specified fd.
// Returns total number of characters printed.
int	ft_printfd(int fd, const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;	

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_formats(fd, args, format[i + 1]);
			i++;
		}
		else
		{
			len += write(fd, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (len);
}
