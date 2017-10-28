#* ************************************************************************** */
#*                                                                            */
#*                                                        :::      ::::::::   */
#*   Makefile                                           :+:      :+:    :+:   */
#*                                                    +:+ +:+         +:+     */
#*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
#*                                                +#+#+#+#+#+   +#+           */
#*   Created: 2017/04/18 03:42:42 by jkrause           #+#    #+#             */
#*   Updated: 2017/06/11 02:45:14 by jkrause          ###   ########.fr       */
#*                                                                            */
#* ************************************************************************** */
# ----------------- Version 1.5 --------------------- #
divert(-1)

# ------------- Real Configuration ------------------ #
define(MK_NUM_OF_TARGETS, 1)
define(MK_FCLEAN_ON_RE, 0)
define(MK_DEBUG, 0)

define(MK_LEM_IN_NAME, lem-in)
define(MK_LEM_IN_ISLIB, 0)
define(MK_LEM_IN_INCLUDE_DIRS, includes)
define(MK_LEM_IN_SRC_DIRS, src libft)
define(MK_LEM_IN_DEBUG, 1)
define(MK_LEM_IN_LITE, 0)

# ------------ Automated Variables ------------------ #
define(MK_AUTO_ISLINUX, ifelse(esyscmd(uname -s | tr -d '\n'), `Darwin', 0, 1))
define(MK_AUTO_COMPILER,ifelse(MK_AUTO_ISLINUX, 1, clang, gcc))

define(MK_LEM_IN_AUTO_SRC_DIR, patsubst(MK_LEM_IN_SRC_DIRS,` ',`````,'''''))
pushdef(`MK_LEM_IN_AUTO_SRC_DIR', ifelse(MK_LEM_IN_SRC_DIRS,.,.,{MK_LEM_IN_AUTO_SRC_DIR}))
define(MK_LEM_IN_AUTO_SRC, esyscmd(bash -c 'find MK_LEM_IN_AUTO_SRC_DIR -type f -name "*.c" | sed -e "s/$/ \\\/g"'))
define(MK_LEM_IN_AUTO_SRC_DIR, patsubst(MK_LEM_IN_SRC_DIRS,` ',```,'''))
define(MK_LEM_IN_AUTO_INCLUDE_DIR, -I patsubst(MK_LEM_IN_INCLUDE_DIRS,` ',``` -I '''))

divert(0)
# ------------- Automated Configuration ------------- #
CFLAGS = ifelse(MK_DEBUG, 1,-g) ifelse(MK_AUTO_ISLINUX,1,-fPIC) -Wall -Werror -Wextra
LEM_IN_NAME = ifelse(MK_LEM_IN_ISLIB, 1, MK_LEM_IN_NAME.a, MK_LEM_IN_NAME)
CFLAGS += MK_LEM_IN_AUTO_INCLUDE_DIR
LEM_IN_SRC = MK_LEM_IN_AUTO_SRC
LEM_IN_OBJ = $(subst .c,.o, $(LEM_IN_SRC))

# ------------------- Targets ----------------------- #

all: $(LEM_IN_NAME)

%.o: %.c
	MK_AUTO_COMPILER $(CFLAGS) -c $? -o $@

$(LEM_IN_NAME): $(LEM_IN_OBJ)
	ifelse(MK_LEM_IN_ISLIB, 0,MK_AUTO_COMPILER $(LEM_IN_OBJ) -o $(LEM_IN_NAME),
	/bin/rm -f $(LEM_IN_NAME)
	ar rcs $(LEM_IN_NAME) $(LEM_IN_OBJ))dnl


re: ifelse(MK_FCLEAN_ON_RE, 1,f)clean all dnl


clean:
	/bin/rm -f $(LEM_IN_OBJ)

fclean: clean
	/bin/rm -f $(LEM_IN_NAME)
