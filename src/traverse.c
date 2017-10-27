/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:17:44 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 20:03:15 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					traverse(t_node *node, int root)
{
	int				g;
	int				res;
	int				m;

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
	m = node->links_count;
	while (++g < m)
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

int					traverse_debug(t_node *node, int root)
{
	if (node->links_count < 1)
	{
		ft_printf("%s: no links\n", node->room_name);
		return (0);
	}
	else if (node->has_end_room)
	{
		ft_printf("%s: has_end_room\n", node->room_name);
		return (1);
	}
	else if (node->has_end_room || node->special_room == 2)
	{
		ft_printf("%s: special_room == 2\n", node->room_name);
		return (1);
	}
	else if (node->has_been_traversed)
	{
		return (0);
	}
	else if (node->special_room == 1 && root > 0)
		return (0);
	node->has_been_traversed = 1;
	int g = -1;
	int res = 0;
	t_node *downstreamed = 0;
	int m = node->links_count;
	while (++g < m)
	{
		ft_printf("%s: Room Number To Try: %s\n", node->room_name, node->links[g]->room_name);
		res += traverse_debug(node->links[g], root + 1);
		if (res)
		{
			ft_printf("Successful! Downlink has end! (%s -> %s) Setting %s's traverse to %d\n", node->room_name, node->links[g]->room_name, node->links[g]->room_name, res);
			ft_printf("Downstream has end room? is end room? or is further down?: %d %d %d\n", node->links[g]->has_end_room, node->links[g]->special_room, res);
			downstreamed = node->links[g];
			node->links[g]->traversal_number = res;
			return (res + 1);
		} else {
			ft_printf("%s: Dead link for node %s\n", node->room_name, node->links[g]->room_name);
		}
	}
	return ((res > 0) ? res + 1 : 0);
}
