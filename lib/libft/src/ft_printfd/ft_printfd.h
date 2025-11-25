/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFD_H
# define FT_PRINTFD_H

# include "libft.h"

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

int		ft_pn_b(int fd, long long n, char *base);
int		ft_print_ptr(int fd, unsigned long long ptr);
int		ft_printchar(int fd, int c);
int		ft_printstr(int fd, char *str);
int		ft_printpct(int fd);
size_t	ft_strlen(const char *s);
void	ft_putstr(int fd, char *str);
int		ft_formats(int fd, va_list args, const char format);
int		ft_printfd(int fd, const char *format, ...);

#endif
