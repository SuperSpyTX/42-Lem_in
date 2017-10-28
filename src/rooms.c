/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:00:13 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/27 16:47:17 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Because the PDF says so :|||||||||||||||||||||||||||||||||||||||||||||||||
*/

int						is_valid_room(char *line)
{
	int					flag;

	if (ft_is_whitespace(*line) || *line == 'L')
		return (0);
	flag = 0;
	line = ft_strchr(line, ' ') + 1;
	while (ft_isdigit(*line) || (!flag && *line == '-'))
	{
		flag = 1;
		line += 1;
	}
	line += 1;
	while (ft_isdigit(*line) || (flag != 2 && *line == '-'))
	{
		flag = 2;
		line += 1;
	}
	if (*line != '\0')
		return (0);
	return ((flag == 2) ? 1 : 0);
}

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
	return (spl);
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
	if (lem_in->arr_end != node)
		node->room_id = lem_in->arr_end->room_id + 1;
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
	if (node->links)
		free(node->links);
	free(node);
}
