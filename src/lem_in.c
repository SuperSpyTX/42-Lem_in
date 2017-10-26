/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:06:15 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 07:27:38 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					recursive(t_node *node, int root)
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
	else if (node->has_been_traversed)
	{
		return (0);
	}
	else if (node->special_room == 1 && root > 0)
		return (0);
	node->has_been_traversed = 1;
	int g = -1;
	int res = 0;
	int m = node->links_count;
	while (++g < m)
	{
		ft_printf("Room Number To Try: %s\n", node->links[g]->room_name);
		res = recursive(node->links[g], root + 1);
		if (res)
		{
			ft_printf("Successful! Downlink has end! -> Setting %s's traverse to %d\n", node->links[g]->room_name, res);
			node->links[g]->traversal_number = res;
		} else {
			ft_printf("Dead link for node %s\n", node->room_name);
		}
	}
	return ((res > 0) ? res + 1 : 0);
}

int					main(int argc, char **argv)
{
	t_lem_in		*lem_in;
	(void)argc;
	(void)argv;
	lem_in = parse_data();
	if (!lem_in || lem_in->error != 0)
		ft_printf("Failed to process Lem_in!\n");
	else
	{
		ft_printf("Successfully processed Lem_in!\n");
		ft_printf("Recursive Result: %d\n", recursive(lem_in->start, 0));
	}
}
