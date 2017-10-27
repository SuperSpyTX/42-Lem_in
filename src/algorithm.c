/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:29:29 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/27 02:57:24 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					check_room(t_node *room)
{
	if (!room)
		return (0);
	if (room->special_room == 1)
		return (0);
	else if (room->ant_number != 0)
		return (0);
	else if (room->special_room == 0 &&
			(room->traversal_number == 0 || room->links_count == 0))
		return (0);
	else if (room->has_end_room || room->special_room == 2)
		return (1);
	else if (!room->has_been_traversed && room->special_room == 0)
		return (0);
	return (1);
}

t_node				*check_links(t_node *room)
{
	int				g;
	t_node			*select;
	t_node			*curr;
	int				priority;

	g = -1;
	priority = INT_MAX;
	select = 0;
	while (++g < room->links_count)
	{
		curr = room->links[g];
		if (check_room(curr) && curr->traversal_number < priority)
		{
			priority = curr->traversal_number;
			select = curr;
		}
	}
	return (select);
}

int					move_lazy_ants(t_lem_in *lem_in)
{
	int				i;
	int				c;
	t_node			*ant_node;
	t_node			*b;

	i = -1;
	c = 0;
	b = 0;
	while (++i < lem_in->num_of_ants)
	{
		ant_node = (!lem_in->ants[i] ? lem_in->start : lem_in->ants[i]);
		if (ant_node == lem_in->end)
		{
			c++;
			continue;
		}
		if (!(b = check_links(ant_node)))
			continue;
		if (!move_ant(i, ant_node, b))
			continue;
		(b ? lem_in->ants[i] = b : 0);
	}
	if (c == lem_in->num_of_ants || i == 0)
		return (0);
	return (1);
}

int					traverse(t_node *node, int root)
{
	int				g;
	int				res;

	if (node->links_count < 1)
		return (0);
	else if (node->has_end_room)
		return (1);
	else if (node->has_been_traversed)
		return (0);
	else if (node->special_room == 1 && root > 0)
		return (0);
	node->has_been_traversed = 1;
	g = -1;
	res = 0;
	while (++g < node->links_count)
	{
		res += traverse(node->links[g], root + 1);
		if (res)
		{
			node->links[g]->traversal_number = res;
			return (res + 1);
		}
	}
	return ((res > 0) ? res + 1 : 0);
}
