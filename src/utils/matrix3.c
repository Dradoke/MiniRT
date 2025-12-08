/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mat4_identity(t_mat4 *out)
{
	t_i32	i;
	t_i32	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				(*out)[i][j] = 1.0f;
			else
				(*out)[i][j] = 0.0f;
			j++;
		}
		i++;
	}
}

void	mat4_translation(t_mat4 *out, t_vec3 v)
{
	mat4_identity(out);
	(*out)[0][3] = v.x;
	(*out)[1][3] = v.y;
	(*out)[2][3] = v.z;
}

void	mat4_scaling(t_mat4 *out, t_vec3 v)
{
	mat4_identity(out);
	(*out)[0][0] = v.x;
	(*out)[1][1] = v.y;
	(*out)[2][2] = v.z;
}
