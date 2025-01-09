/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:34:49 by ttouahmi          #+#    #+#             */
/*   Updated: 2025/01/09 13:07:28 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <term.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BLUE			"\001\e[38;2;47;160;219m\002"
#define RED			"\e[38;5;196m"
#define RESET			"\001\e[0m\002"
#define ENV			__environ

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
	QUOTED, // "WORD"
}	t_type;

typedef struct env
{
	struct env	*next;
	char		*value;
	char		*name;
}	t_env;

typedef struct token
{
	unsigned int	err;
	unsigned int	tlen;
	t_env 			*envhead;
	char			**word;
	t_type			*type;
}	t_token;

void			print_array(char **array);
void			print_token(t_token *token);

void			exec(t_token *token, unsigned int *i);
void			cd(t_token *token, unsigned int *i);
void			pwd(t_token *token, unsigned int *i);
void			export(t_token *token, unsigned int *i);
void			unset(t_token *token, unsigned int *i);
void			env(t_token *token, unsigned int *i);
void			echo(t_token *token, unsigned int *i);

void			free_env(t_token *token);
t_env			*ft_lstnew(char *content);
void			ft_env_print(t_env *env);

void			free_word(t_token *token);
void			erased_str(t_token *token, unsigned int *s);
void			erased_quote(t_token *token, unsigned int *p);
unsigned int	wich_type(char c);
char			*ft_strcpy(char *str1);
char			*ft_strjoin(char *s1, char *s2);
unsigned int	parsing(t_token *token);
void			print_error(t_token *token, unsigned int n);
unsigned int	is_sep(char c);
void			lexer(t_token *token, char *input);
void			get_type(t_token *token, unsigned int one, unsigned int two);
void			parsing_exec(t_token *token, unsigned int *i);
unsigned int	malloc_word(t_token *token, char *input, unsigned int c);
unsigned int	count_word(char *str);
unsigned int	ft_strcmp(char *str, char *str2);
unsigned int	ft_strlen(char *str);
void			free_token(t_token *token);
int				exitmentioned(t_token *token);
void			toklen(t_token *token);
int				secnd_quote(t_token *token, unsigned int *one, t_type quote);
