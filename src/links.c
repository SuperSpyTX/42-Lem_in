/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 22:58:14 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/27 01:42:05 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						append_link(t_node *parent, t_node *node)
{
	t_node				**nset;

	if (!parent || !node)
		return (0);
	nset = ft_memalloc((parent->links_count + 2) * sizeof(t_node*));
	ft_memcpy(nset, parent->links, sizeof(t_node*) * parent->links_count);
	if (parent->links_count != 0)
		free(parent->links);
	nset[parent->links_count++] = node;
	nset[parent->links_count] = 0;
	if (node->special_room == 2)
		parent->has_end_room = 1;
	parent->links = nset;
	return (1);
}

int						merge_link(t_node *parent, t_node *child)
{
	if (!append_link(parent, child))
		return (0);
	return (append_link(child, parent));
}
