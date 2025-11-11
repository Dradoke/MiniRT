/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MV42                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by MV42              #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by MV42             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••TYPE

// INTEGER	1 byte  | 8  bits
typedef unsigned char		t_ui8;
typedef signed char			t_i8;
// INTEGER	2 bytes | 16 bits
typedef unsigned short		t_ui16;
typedef signed short		t_i16;
// INTEGER	4 bytes | 32 bits
typedef unsigned int		t_ui32;
typedef signed int			t_i32;
// INTEGER	8 bytes | 64 bits
typedef unsigned long long	t_ui64;
typedef signed long long	t_i64;
// FLOAT	4 bytes | 32 bits
typedef float				t_f32;
// FLOAT	8 bytes | 64 bits
typedef double				t_f64;

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••BOOLEAN

typedef t_ui8				t_bool;
enum e_bool
{
	FALSE,
	TRUE,
};

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••LIBFT
/*LibC Functions*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *str, const char *find, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t size);
char	*ft_strdup(const char *s1);

// Additional Functions

char	*ft_substr(char const *s, t_ui32 start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(t_ui32, char));
void	ft_striteri(char *s, void (*f)(t_ui32, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Bonus Functions

typedef struct s_list
{
	struct s_list	*prev;
	int				index;
	void			*content;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••GET_NEXT_LINE

char	*get_next_line(int fd);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••FT_PRINTFD

int		ft_printfd(int fd, const char *format, ...);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••CUSTOM

int		ft_abs(int x);
t_f64	ft_atod(const char *str);
t_f32	ft_atof(const char *str);
int		ft_atoi_base(char *str, char *base);
long	ft_atol(const char *s);
t_f32	ft_degtorad(t_f32 deg);
int		ft_isspace(char c);
int		ft_isspace_nl(char c);
t_f32	ft_radtodeg(t_f32 rad);
char	*ft_rand_str(size_t len);
void	*ft_realloc(void *original, size_t size);
void	ft_skipspace(char *str, int *i);
char	**ft_split_charset(const char *s, const char *charset);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_vfree(int count, ...);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#endif
