/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:29:34 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 16:56:32 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						move_ant(int ant, t_node *a, t_node *b)
{
	if (!a || !b)
		return (0);
	if (b->special_room == 0)
		b->ant_number = ant + 1;
	if (a->special_room == 0)
		a->ant_number = 0;
	ft_printf("L%d-%s ", ant + 1, b->room_name);
	return (1);
}

/*
** Evaluate this function and it's sole purpose in life.
*/
int						create_exclusive_network_event4elitesonly(t_lem_in *lem_in)
{
	if (!(lem_in->ants = (t_node**)ft_memalloc(sizeof(t_node*) * (lem_in->num_of_ants + 1))))
		return (0);
	return (1);
}
