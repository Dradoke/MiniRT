#include "minirt.h"

/// @brief Converts str in t_rgba where a is 1.
/// @param str String with 3 number values [0:255] delimited by
/// ',' only, in the strict order : r,g,b
/// @param color Address of t_rgba var where converted values will be stored
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_color(char *str, t_rgba *color)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!str)
			return (FALSE);
		color->rgba[i] = (t_ui8)ft_atoi(str);
		str = ft_strchr(str, ',');
		if (!str && i < 2)
			return (FALSE);
		if (str)
			str++;
		i++;
	}
	color->a = 255;
	return (TRUE);
}

/// @brief Converts str to t_vec3
/// @param str String with 3 number values within double type range delimited by
/// ',' only, in the strict order : x,y,z
/// @param vec3 Address of t_vec3 var where converted values will be stored
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_vec3(char *str, t_vec3 *vec3)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!str)
			return (FALSE);
		vec3->v[i] = ft_atof(str);
		str = ft_strchr(str, ',');
		if (!str && i < 2)
			return (FALSE);
		if (str)
			str++;
		i++;
	}
	return (TRUE);
}

/// @brief Converts str to vec3 and checks if between normalized range 
/// [-1.0:1.0]
/// @param str String with 3 number values within [-1.0:1.0] range delimited 
/// by ',' only, in the strict order : x,y,z
/// @param vec3 Address of t_vec3 var where converted values will be stored
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_normal_vec3(char *str, t_vec3 *vec3)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!str)
			return (FALSE);
		vec3->v[i] = ft_atof(str);
		if (vec3->v[i] < -1.0 || vec3->v[i] > 1.0)
			return (FALSE);
		str = ft_strchr(str, ',');
		if (!str && i < 2)
			return (FALSE);
		if (str)
			str++;
		i++;
	}
	return (TRUE);
}
