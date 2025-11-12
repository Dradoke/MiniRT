#include "minirt.h"

/// @brief 
/// @param str 
/// @param brightness 
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_brightness(char *str, t_f32 *brightness)
{
	if (!str)
		return (FALSE);
	*brightness = ft_atof(str);
	if (*brightness < 0.0 || *brightness > 1.0)
		return (FALSE);
	return (TRUE);
}

/// @brief 
/// @param str 
/// @param aov 
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_aov(char *str, t_ui8 *aov)
{
	if (!str)
		return (FALSE);
	*aov = (t_ui8)ft_atoi(str);
	if (*aov > 180)
		return (FALSE);
	return (TRUE);
}

/// @brief 
/// @param str 
/// @param size 
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_size(char *str, t_f32 *size)
{
	if (!str)
		return (FALSE);
	*size = ft_atof(str);
	if (*size < 0.0)
		return (FALSE);
	return (TRUE);
}
