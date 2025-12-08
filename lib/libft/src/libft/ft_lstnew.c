/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Creates a new list node.
// Allocates and initializes a node with 'content' and NULL next pointer.
// Returns the new node or NULL if allocation fails.
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_calloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	return (node);
}
