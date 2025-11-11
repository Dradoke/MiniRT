#ifndef PROTOTYPE_H
# define PROTOTYPE_H
# include "minirt.h"

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

t_bool	ft_parser(t_data *data, char *filename);

t_bool	parse_unique(t_data *data, char **token);
t_bool	parse_mesh(t_data *data, char **token);

t_bool	color_parser(char *str, t_rgba *color);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#endif
