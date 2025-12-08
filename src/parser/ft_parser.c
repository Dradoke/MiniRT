/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Checks if the filename ends with '.rt'
/// @param name The filename
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
static t_bool	filename_is_rt(char *name)
{
	while (*name)
		name++;
	name -= 3;
	if (name[0] == '.' && name[1] == 'r' && name[2] == 't')
		return (TRUE);
	return (FALSE);
}

static t_bool	parse_object(t_data *data, char **token)
{
	if (!ft_strcmp(token[0], "A") || !ft_strcmp(token[0], "C")
		|| !ft_strcmp(token[0], "L"))
		return (parse_unique(data, token));
	else if (!ft_strcmp(token[0], "sp") || !ft_strcmp(token[0], "pl")
		|| !ft_strcmp(token[0], "cy") || !ft_strcmp(token[0], "tr"))
	{
		if (!parse_mesh(data, token))
			return (FALSE);
		(data->scene.obj_count[MESH])++;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	parse_line(t_data *data, char *line)
{
	char	**token;

	token = ft_split_charset(line, " \t\v\f\r");
	if (!token || !token[0] || !parse_object(data, token))
		return (free(token), FALSE);
	return (free(token), TRUE);
}

/// @brief Checks if the global list is valid, only one A and one C at most
/// @param list The list of objects used in parsing
/// @return t_bool
/// @retval 1 / TRUE	- If successful
/// @retval 0 / FALSE	- If error
static t_bool	is_valid_list(t_list *list)
{
	char	ambient_count;
	char	cam_count;

	ambient_count = 1;
	cam_count = 1;
	while (list)
	{
		if (list->content && ((t_node *)list->content)->type == A)
			ambient_count--;
		if (list->content && ((t_node *)list->content)->type == C)
			cam_count--;
		list = list->next;
	}
	if (ambient_count || cam_count)
		return (FALSE);
	return (TRUE);
}

t_bool	ft_parser(t_data *data, char *filename)
{
	t_bool	valid_flag;

	if (!filename_is_rt(filename))
		return (ft_error(data, EXIT_FAILURE, FTERR_EXTENSION), FALSE);
	data->fd_file = open(filename, O_RDONLY);
	if (data->fd_file <= 2)
		return (ft_error(data, EXIT_FAILURE, FTERR_FILE), FALSE);
	data->line = get_next_line(data->fd_file);
	valid_flag = TRUE;
	while (data->line)
	{
		if (data->line[0] != '\n')
			valid_flag = parse_line(data, data->line);
		if (!valid_flag)
			return (ft_error(data, EXIT_FAILURE, FTERR_PARSE), FALSE);
		free(data->line);
		data->line = get_next_line(data->fd_file);
	}
	if (!is_valid_list(data->parse_list) || !ft_lst_to_arr(data))
		return (ft_error(data, EXIT_FAILURE, FTERR_PARSE), FALSE);
	return (TRUE);
}
