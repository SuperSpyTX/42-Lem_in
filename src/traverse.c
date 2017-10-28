/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:08:09 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/27 20:51:04 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					trav_check_room(t_node *node, int root)
{
	if (node->links_count < 1)
		return (2);
	else if (node->special_room == 2)
		return (1);
	else if (node->has_been_traversed)
		return (2);
	else if (node->special_room == 1 && root > 0)
		return (2);
	return (0);
}

int					traverse(t_node *node, int root)
{
	int				res;
	int				g;
	int				t;

	res = trav_check_room(node, root);
	if (res > 0)
		return ((res == 2 ? 0 : res));
	g = -1;
	t = 0;
	node->has_been_traversed = 1;
	while (++g < node->links_count)
	{
		t = traverse(node->links[g], root + 1);
		if (t)
		{
			res += t;
			node->links[g]->traversal_number = res;
			if (root > 0)
				return (res + 1);
		}
	}
	return ((res > 0) ? res + 1 : 0);
}
