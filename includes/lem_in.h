/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:12:35 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/27 01:42:48 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

/*
** Node:
** special_room = (2 == End Room, 1 == Start Room)
** I have to include the original line because 42 expects me to parse
** some numbers :joy:
*/
typedef struct			s_node
{
	int					traversal_number;
	int					ant_number;
	char				*room_name;
	int					special_room;
	int					has_end_room;
	int					has_been_traversed;
	int					links_count;
	struct s_node		**links;
	struct s_node		*next;
}						t_node;

/*
** Lem_in:
** "When life gives you lem_ins...."
** ...._blank_
*/
typedef struct			s_lem_in
{
	int					error;
	t_node				*start;
	t_node				*end;
	t_node				*arr_start;
	t_node				*arr_end;
	int					num_of_ants;
	t_node				**ants;
}						t_lem_in;

/*
** Function prototypes.
*/
t_lem_in				*parse_data(void);
int						append_room(t_lem_in *lem_in, t_node *node, int sp);
void					free_room(t_node *node);
int						append_link(t_node *parent, t_node *node);
int						merge_link(t_node *parent, t_node *child);
char					**spl_room_names(char *line);
int						create_exclusive_network_event4elite(t_lem_in *lem_in);
int						move_ant(int ant, t_node *a, t_node *b);
int						move_lazy_ants(t_lem_in *lem_in);
int						is_valid_room(char *line);
int						traverse(t_node *node, int root);
int						traverse_debug(t_node *node, int root);

#endif
