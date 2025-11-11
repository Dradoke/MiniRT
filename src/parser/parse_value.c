#include "minirt.h"

/// @brief Converts str in t_rgba where a is 1.
/// @param str String with 3 number values between 0 and 255 delimited by
/// ',' only, in the strict order : r,g,b
/// @param color Address of t_rgba var where converted values will be stored
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	color_parser(char *str, t_rgba *color)
{
	t_ui8	*components[3];
	int		i;

	components[0] = &color->r;
	components[1] = &color->g;
	components[2] = &color->b;
	i = 0;
	while (i < 3)
	{
		if (!str)
			return (FALSE);
		*components[i] = (t_ui8)ft_atoi(str);
		if (*components[i] > 255)
			return (ft_putstr_fd(FTERR_COLOR_RANGE, 2), FALSE);
		str = ft_strchr(str, ',');
		if (!str && i < 2)
			return (FALSE);
		if (str)
			str++;
		i++;
	}
	color->a = 1.0f;
	return (TRUE);
}

/// @brief Converts str in t_vec3
/// @param str String with 3 number values within double type range delimited by
/// ',' only, in the strict order : x,y,z
/// @param vec3 Address of t_vec3 var where converted values will be stored
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool vec3_parser(char *str, t_vec3 *vec3)
{

}
