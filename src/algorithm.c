/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:29:29 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 23:53:31 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

# define CONT c++; continue;

int					check_room(t_node *room)
{
	if (!room)
		return (0);
	//ft_printf("%s(%d): %d != 0 %d > 0 %d == 0 %d != 0\n", room->room_name, room->ant_number, room->special_room, room->has_been_traversed, room->traversal_number, room->links_count);
	if (room->special_room == 2)
		return (1);
	else if (room->ant_number != 0)
		return (0);
	else if (room->has_end_room)
		return (1);
	else if (!room->has_been_traversed)
		return (0);
	else if (room->traversal_number == 0 || room->links_count == 0)
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
		//ft_printf("%s -> %s\n", room->room_name, curr->room_name);
		if (check_room(curr) && curr->traversal_number < priority)
		{
			priority = curr->traversal_number;
			select = curr;
			//ft_printf("Found room: %s (%d)\n", curr->room_name, priority);
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
		//ft_printf("\nMoving ant %d\n\n", i + 1);
		ant_node = (!lem_in->ants[i] ? lem_in->start : lem_in->ants[i]);
		if (ant_node == lem_in->end)
		{
			CONT;
		}
		if (!(b = check_links(ant_node)))
		{
		//	ft_printf("No possible links?");
			continue;
		}
		if (!move_ant(i, ant_node, b))
		{
		//	ft_printf("Can't move ant...");
			continue;
		}
		(b ? lem_in->ants[i] = b : 0);
	}
	//ft_printf("C: %d\n", c);
	if (c == lem_in->num_of_ants || i == 0)
		return (0);
	return (1);
}
