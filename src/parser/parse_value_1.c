/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Converts str in t_f32 representing the brightness in range [0.0:1.0]
/// @param str String with 1 float number [0.0:1.0]
/// @param brightness Address of t_f32 var where converted values will be stored
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

/// @brief Converts str in t_ui8 representing the AOV in range [0:360]
/// @param str String with 1 integer number [0:360]
/// @param aov Address of t_ui16 var where converted values will be stored
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
t_bool	parse_aov(char *str, t_ui16 *aov)
{
	if (!str)
		return (FALSE);
	*aov = (t_ui16)ft_atoi(str);
	if (*aov > 360)
		return (FALSE);
	return (TRUE);
}

/// @brief Converts str in t_f32 representing a size in range [0.0:max]
/// @param str String with 1 float number [0.0:max]
/// @param size Address of t_f32 var where converted values will be stored
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
