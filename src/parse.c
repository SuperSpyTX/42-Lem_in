/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:23:41 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/27 20:41:11 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Please forgive me for my sins
** for the acts I have committed to the Norminette.
** This is the only file where the offense has been committed.
** This is also in the spirit of "When norm gives you lem_ins...."
*/

t_node						*parse_room(char *line)
{
	t_node					*node;

	ALOKATE(node, t_node);
	if (*line == '#' || !ft_strchr(line, ' '))
	{
		FREE_RET(node, 0);
	}
	node->room_name = ft_strchr(line, ' ');
	NAWL_GUARD(node->room_name = ft_strsub(line, 0, (node->room_name - line)));
	if (!is_valid_room(line))
	{
		FREE2_RET(node->room_name, node, 0);
	}
	node->links_count = 0;
	node->room_id = 0;
	ft_printf("%s\n", line);
	return (node);
}

int							parse_room_link(t_lem_in *lem_in, char *line)
{
	char					**spl;
	t_node					*trav;
	t_node					*nodea;
	t_node					*nodeb;

	nodea = 0;
	nodeb = 0;
	spl = spl_room_names(line);
	if (!spl)
	{
		FREE_RET(line, 0);
	}
	trav = lem_in->arr_start;
	while (trav)
	{
		if (nodea && nodeb)
			break ;
		if (!nodea && ft_strequ(trav->room_name, spl[0]))
			nodea = trav;
		if (!nodeb && ft_strequ(trav->room_name, spl[1]))
			nodeb = trav;
		trav = trav->next;
	}
	ft_printf("%s\n", line);
	FREE3_RET(spl[0], spl, line, merge_link(nodea, nodeb));
}

int							process_special_command(char *line)
{
	int						sp;

	if (*line == '#')
	{
		ft_printf("%s\n", line);
		if (ft_strstr(line, "##start"))
			sp = 1;
		else if (ft_strstr(line, "##end"))
			sp = 2;
		else
		{
			free(line);
			sp = 3;
		}
		return (sp);
	}
	return (0);
}

int							iterate_rooms(t_lem_in *lem_in)
{
	int						sp;
	t_node					*node;

	LINE_BY_LINE(0);
	sp = process_special_command(line);
	CONTINUE_IF(sp == 3);
	if (ft_strchr(line, '-') && !ft_strchr(line, ' ')
			&& sp == 0 && lem_in->arr_start)
	{
		CONTINUE_IF(parse_room_link(lem_in, line));
		return (0);
	}
	if (sp == 0)
		node = parse_room(line);
	else
	{
		GL_FREE(0, parse_room, node);
	}
	if (!append_room(lem_in, node, sp))
	{
		CALL_FREE2_RET(free_room(node), free(line), 0);
	}
	free(line);
	CLOSE_LOOP;
	return (1);
}

t_lem_in					*parse_data(void)
{
	t_lem_in				*lem_in;
	char					*first_line;

	ALOKATE(lem_in, t_lem_in);
	lem_in->error = 1;
	if (!get_next_line(0, &first_line))
		return (lem_in);
	else if (ft_strchr(first_line, '-'))
	{
		FREE_RET(first_line, lem_in);
	}
	USE_VAR_FUNC(first_line, ft_atoi, lem_in->num_of_ants);
	if (lem_in->num_of_ants < 1)
	{
		lem_in->error = 1;
		return (lem_in);
	}
	ft_printf("%d\n", lem_in->num_of_ants);
	if (iterate_rooms(lem_in))
		lem_in->error = 0;
	if (!lem_in->start || !lem_in->end || lem_in->start->links_count < 1)
		lem_in->error = 1;
	return (lem_in);
}
