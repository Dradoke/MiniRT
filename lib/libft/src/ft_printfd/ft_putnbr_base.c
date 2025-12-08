/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printfd.h"
#include "libft.h"

// Prints a number in a specified base.
// Recursively converts and writes 'n' using the characters in 'base'.
// Returns number of characters printed.
int	ft_pn_b(int fd, long long n, char *base)
{
	uintmax_t	nbr;
	uintmax_t	base_length;
	int			len;

	len = 0;
	base_length = ft_strlen(base);
	if (n < 0)
	{
		len += write(fd, "-", 1);
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr >= base_length)
		len += ft_pn_b(fd, nbr / base_length, base);
	len += write(fd, &base[nbr % base_length], 1);
	return (len);
}

// Prints a pointer address in hexadecimal format.
// Handles NULL pointers by printing "(nil)" instead of an address.
// Returns number of characters printed.
int	ft_print_ptr(int fd, unsigned long long ptr)
{
	int			len;
	uintmax_t	nbr;
	uintmax_t	base_length;
	char		*base;

	if (ptr == 0)
		return (write(fd, "(nil)", 5));
	len = write(fd, "0x", 2);
	base = "0123456789abcdef";
	base_length = 16;
	nbr = ptr;
	if (nbr >= base_length)
		len += ft_pn_b(fd, nbr / base_length, base);
	len += write(fd, &base[nbr % base_length], 1);
	return (len);
}
