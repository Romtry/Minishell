# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 13:44:10 by rothiery          #+#    #+#              #
#    Updated: 2025/02/11 13:38:11 by rothiery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	minishell

SRC= 	src/main.c			src/parsing.c		src/str_utils.c		src/test.c				\
		src/malloc_utils.c	src/dollar_pars.c	src/pars_utils.c	src/lexer.c				\
		src/quotes_pars.c	src/lst_utils.c		src/transfert.c		src/free_utils.c		\
		src/exec/bultin.c	src/exec/execcmd.c	src/exec/execpipe.c	src/exec/execexterne.c	\
		src/exec/redir.c	src/exec/utils.c	\

OFILES= ${SRC:%.c=obj/%.o}

CC= 	cc
CFLAGS= -Wall -Wextra -Werror -fsanitize=address -g3 -I includes
RESET = \033[0m
GRAS = \033[1m
ITALIQUE = \033[3m
SOULIGN = \033[4m
UP = \033[A
BLINK = \033[6m

ORANGE = \033[38;5;216m
DARKBLUE = \033[38;5;21m
LIGHT_RED = \033[38;5;196m
RED = \033[38;5;130m
DARK_RED = \033[38;5;88m
GREEN = \033[38;5;85m

#change value with number of src files !
NBR_TOT_FICHIER = 20

FICH_COUNT = 0
NBR_COMPILER = ${shell expr 100 \* ${FICH_COUNT} / ${NBR_TOT_FICHIER}}
BAR =  ${shell expr 23 \* ${FICH_COUNT} / ${NBR_TOT_FICHIER}}
REST = ${shell expr 23 - ${BAR}}

all:	${NAME}

${NAME}:		${OFILES}
	@${CC} ${CFLAGS} -lreadline ${OFILES} -o ${NAME}
	@echo "\n\n${GREEN}[✓] - ${_GREEN}${NAME}${GREEN} Successfully Compiled!${RESET}"

obj/%.o:%.c
	@mkdir -p obj/$(dir $<)
	@${eval FICH_COUNT = ${shell expr ${FICH_COUNT} + 1}}
	@${CC} ${CFLAGS} -c $< -o $@
	@file_name=$(notdir $<) && \
	echo " ${GRAS}${RED}-> COMPILATION EN COURS${RESET}${GRAS}${GREEN}${RESET}" && \
	printf " ${RED}${GRAS}[${GREEN}%-.${BAR}s${DARK_RED}%-.${REST}s${RED}] [%d/%d (%d%%)] ${GREEN}%s  ✓                         ${DEF_COLOR}" "-----------------------" "-----------------------" ${FICH_COUNT} ${NBR_TOT_FICHIER} ${NBR_COMPILER} $${file_name} && \
	echo "${UP}${UP}${UP}" && \
	echo ""

clean:
	@rm -rf obj
	@rm -f ${NAME}.log
	@echo "${ORANGE}${GRAS}\tNETTOYAGE${RESET}"
	@echo "${RED}${ITALIQUE} -les fichiers sont supprimés${RESET}"

fclean:	clean
	@rm -f ${NAME}
	@${RM} ${NAME}
	@echo "${RED}${ITALIQUE} -${NAME} est supprimê${RESET}"

re:	fclean all

.PHONY:		all bonus clean fclean re
