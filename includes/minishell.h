/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:34:49 by ttouahmi          #+#    #+#             */
/*   Updated: 2024/12/24 10:14:45 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLUE			"\e[38;2;47;160;219m"

typedef enum e_type
{
	WORD,
	SEP, // whitespace
	PIPE, // |
	INPUTREDIR, // <
	OUTPUTREDIR, // >
	HEREDOC, // <<
	APPENDREDIR, // >>
	SINGLEQUOTE, // '
	DOUBLEQUOTE, // "
	DOLLAR, // $
	EMPTY, // NULL
} t_type;

typedef struct token
{
	unsigned int	tlen;
	char			**word;
	t_type			*type;
}	t_token;

void			print_token(t_token *token);

unsigned int	is_sep(char c);
void			lexer(t_token *token, char *input);
void			get_type(t_token *token);
void			parsing(t_token *token, unsigned int i);
unsigned int	malloc_word(t_token *token, char *input, unsigned int c);
unsigned int	count_word(char *str);
unsigned int	ft_strcmp(char *str, char *str2);
unsigned int	ft_strlen(char *str);
void			free_token(t_token *token);
int				exitmentioned(t_token *token);
void			echo(t_token *token, unsigned int i);
void			toklen(t_token *token);
