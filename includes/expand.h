/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 20:16:43 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/26 06:32:40 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

char				*expand_pad(char c, int repeat,
						char *result, int *bsize);
void				*expand_write(void *dst, int dstlen,
						void *src, int *srcsize);
void				*expand_get_next_line_until(int fd, void *(*f)(char*));

/*
** Really shitty ft-macros 2.0
** Not original, not funny memes, and no facts only.
** To be most hated by correctors
** To be hated by roblabla as well :) (maybe)
*/
# define ALOKATE(A, B) NAWL_GUARD(A = ft_memalloc(sizeof(B)));
# define GIT_LINE(A, B, C) char *g = 0; get_next_line(A, &g); C = B(g);
# define GIT_LINE_FREE(A, B, C) char *g = 0; get_next_line(A, &g); C = B(g); free(g);
# define LINE_BY_LINE(A) char *line = 0; while (get_next_line(A, &line)) {
# define CLOSE_LOOP }

# define MULTI_FREE(A, B, C) free(A); free(B); free(C);

# define FREE_RET(A, B) free(A); return (B);
# define FREE2_RET(A, B, C) free(A); free(B); return (C);
# define FREE3_RET(A, B, C, D) free(A); free(B); free(C); return (D);
# define FREE4_RET(A, B, C, D, E) free(A); free(B); free(C); free(D); return (E);

# define CALL_FREE2_RET(A, B, C) A; B; return (C);

# define LAZY_IF(A) if (A) {
# define LAZY_ELSECONT else { continue; }
# define LAZY_ELSEIF(A) } else if (A) {
/*
** I'm stealing this idea from Logan because I can.
*/
# define NAWL_GUARD(A) if (!(A)) { return ((void*)0); }
#endif
