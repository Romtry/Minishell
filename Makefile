# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 13:44:10 by rothiery          #+#    #+#              #
#    Updated: 2025/03/11 09:08:26 by rothiery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	minishell

VPATH=	src																		\
		src/exec																\
		src/exec/execext														\
		src/exec/bultin															\
		src/exec/bultin/cd														\
		src/exec/bultin/redir													\
		src/exec/bultin/export													\
		src/exec/utils															\
		src/exec/env_exec														\
		src/fonc_utils															\
		src/fonc_utils/comp														\
		src/fonc_utils/str														\
		src/parsing_part									 					\
		src/parsing_part/parsing												\
		src/parsing_part/parsing/utils											\
		src/parsing_part/parsing/quote_utils									\
		src/parsing_part/transfert_utils										\

SRC= 	main.c					get_env.c				test.c					\
		echo.c					env_exit.c				search.c				\
		ft_export.c				pwd.c					cd2.c					\
		redir.c					unset.c					get_env_h.c				\
		sews.c					handle_child.c			var.c					\
		exec_b.c				execcmd.c				execext.c				\
		pipe.c					comp.c					heredoc.c				\
		lst_utils.c				type.c					get_cmd_path.c			\
		erased_str.c			ft_split.c				cd.c 					\
		ft_strjoin.c			lexer_utils.c			count_args.c			\
		ft_strlen.c				copies.c				free_utils.c			\
		dollar_inquote.c		erased_quote.c			quote_type.c			\
		realloc_word.c			second_quote.c			dollar_utils.c			\
		dollar_quote.c			parsing.c				print_error.c			\
		pipe_pars.c				redir_pars.c			sep_clean.c				\
		malloc_array.c			no_pipe.c				transfert_pipe.c		\
		transfert.c				in_redir.c				pars_heredoc.c			\
		out_redir.c				alloc_utils.c

OFILES= ${SRC:%.c=obj/%.o}

CC= 	cc	-Wextra -Wall
CFLAGS= -g3 -I includes
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
NBR_TOT_FICHIER = 70

FICH_COUNT = 0
NBR_COMPILER = ${shell expr 100 \* ${FICH_COUNT} / ${NBR_TOT_FICHIER}}
BAR =  ${shell expr 23 \* ${FICH_COUNT} / ${NBR_TOT_FICHIER}}
REST = ${shell expr 23 - ${BAR}}

all:	${NAME}

${NAME}:		${OFILES}
	   @${CC} ${CFLAGS} ${OFILES} -o ${NAME} -lreadline -lncurses
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
