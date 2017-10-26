/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:00:13 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 06:26:50 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char					**spl_room_names(char *line)
{
	char				*room1;
	char				*room2;
	char				**spl;

	room2 = ft_strchr(line, '-') + 1;
	if (!room2)
		return (0);
	room1 = ft_strsub(line, 0, (room2 - 1 - line));
	NAWL_GUARD(spl = (char**)ft_memalloc(sizeof(char*) * 2));
	spl[0] = room1;
	spl[1] = room2;
	return spl;
}

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

int						append_room(t_lem_in *lem_in, t_node *node, int sp)
{
	if (!node || !lem_in)
		return (0);
	if (sp == 2 && lem_in->end)
		return (0);
	else if (sp == 1 && lem_in->start)
		return (0);
	if (!lem_in->arr_start)
		lem_in->arr_start = node;
	if (!lem_in->arr_end)
		lem_in->arr_end = node;
	else if (!lem_in->arr_end->next)
	{
		lem_in->arr_end->next = node;
		lem_in->arr_end = node;
	}
	if (sp > 0)
		node->special_room = sp;
	if (sp == 2)
		lem_in->end = node;
	else if (sp == 1)
		lem_in->start = node;
	return (1);
}

void					free_room(t_node *node)
{
	if (!node)
		return ;
	if (node->room_name)
		free(node->room_name);
	if (node->room_line)
		free(node->room_line);
	if (node->links)
		free(node->links);
	free(node);
}
