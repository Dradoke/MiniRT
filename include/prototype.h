#ifndef PROTOTYPE_H
# define PROTOTYPE_H
# include "minirt.h"

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

// see_data.c
void	see_data(t_data *data);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

// ft_lst_to_arr.c
t_bool	ft_lst_to_arr(t_data *data);

// ft_parser.c
t_bool	ft_parser(t_data *data, char *filename);

// parse_mesh.c
t_bool	parse_mesh(t_data *data, char **token);

// parse_unique.c
t_bool	parse_unique(t_data *data, char **token);

// parse_value_1.c
t_bool	parse_brightness(char *str, t_f32 *brightness);
t_bool	parse_aov(char *str, t_ui8 *aov);
t_bool	parse_size(char *str, t_f32 *size);

// parse_value_2.c
t_bool	parse_color(char *str, t_rgba *color);
t_bool	parse_vec3(char *str, t_vec3 *vec3);
t_bool	parse_normal_vec3(char *str, t_vec3 *vec3);

// ft_error.c
void	*safe_calloc(t_data *data, t_ui32 size);
void	ft_clean_all(t_data	*data);
void	ft_error(t_data *data, int error_code, char *error_message);

// matrix.c
t_mat4	mat4_identity(void);
t_mat4	mat4_translation(t_vec3 v);
t_mat4	mat4_scaling(t_vec3 v);
t_mat4	mat4_multiply(t_mat4 a, t_mat4 b);
t_mat4	mat4_look_at(t_vec3 from, t_vec3 to, t_vec3 up_temp);

// vector1.c
t_vec3	vec3_new(t_f32 x, t_f32 y, t_f32 z);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_scale(t_vec3 v, t_f32 s);
t_f32	vec3_dot(t_vec3 v1, t_vec3 v2);

// vector2.c
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
t_f32	vec3_length_sq(t_vec3 v);
t_f32	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_rotate(t_vec3 v, t_vec3 axis, t_f32 angle);

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#endif
