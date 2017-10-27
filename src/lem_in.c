/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:06:15 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 20:29:31 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		ft_printf("Successfully processed Lem_in!\n\n\n\n\n");
		if (!traverse(lem_in->start, 0))
			ft_printf("There are no valid links!\n");
		else
			if (create_exclusive_network_event4elitesonly(lem_in))
				while (move_lazy_ants(lem_in))
					ft_printf("\n");
	}
}
