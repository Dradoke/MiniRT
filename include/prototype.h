#ifndef PROTOTYPE_H
# define PROTOTYPE_H
# include "minirt.h"
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

t_bool	ft_render(t_data *data);

void	see_data(t_data *data);

t_bool	ft_lst_to_arr(t_data *data);

void	ft_error(t_data *data, int error_code, char *error_message);
void	ft_clean_all(t_data	*data);

void	ft_hooks(t_data *data);

t_bool	ft_parser(t_data *data, char *filename);

t_bool	parse_unique(t_data *data, char **token);
t_bool	parse_mesh(t_data *data, char **token);

t_bool	parse_brightness(char *str, t_f32 *brightness);
t_bool	parse_aov(char *str, t_ui8 *aov);
t_bool	parse_size(char *str, t_f32 *size);

t_bool	parse_color(char *str, t_rgba *color);
t_bool	parse_vec3(char *str, t_vec3 *vec3);
t_bool	parse_normal_vec3(char *str, t_vec3 *vec3);

t_mat4	mat4_identity(void);
t_mat4	mat4_translation(t_vec3 v);
t_mat4	mat4_scaling(t_vec3 v);
t_mat4	mat4_multiply(t_mat4 a, t_mat4 b);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
#endif