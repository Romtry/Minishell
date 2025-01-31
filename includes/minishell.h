/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:34:49 by ttouahmi          #+#    #+#             */
/*   Updated: 2025/01/28 11:44:49 by rothiery         ###   ########.fr       */
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
#define	CLEAR		"\e[0m\n"
#define ENV			__environ

typedef enum e_type
{
	END,
	WORD,
	SEP, // whitespace
	PIPE, // |
	INPUTREDIR, // <
	OUTPUTREDIR, // >
	HEREDOC, // <<
	APPENDREDIR, // >>
	SQUOTE, // '
	DQUOTE, // "
	DOLLAR, // $
	EMPTY, // NULL
	DQUOTED, // "WORD"
	SQUOTED, // 'WORD'
}	t_type;

typedef struct env
{
	struct env	*next;
	char		*value;
	char		*name;
}	t_env;

typedef struct cmd
{
	t_type		**type;
	char		***word;
}	t_cmd;

typedef struct token
{
	unsigned int	err;
	unsigned int	tlen;
	t_env			*envhead;
	char			**word;
	t_type			*type;
}	t_token;

void			print_array(char **array);
void			print_token(t_token *token);
void			print_cmd(t_cmd *cmd);
void			env_print(t_env *env);

// dollar_pars
void			dollar_quote(t_token *token, unsigned int i);
void			pars_dollar(t_token *token, unsigned int i);
void			dollar_pars(t_token *token, unsigned int *i, unsigned int *exit_stat);

// free_utils
void			free_cmd(t_cmd	*cmd);
void			free_token(t_token *token);
void			free_env(t_token *token);
void			free_word(t_token *token);

// lexer
void			lexer(t_token *token, char *input);
unsigned int	malloc_word(t_token *token, char *input, unsigned int c);
unsigned int	count_word(char *str);
void			lexer(t_token *token, char *input);

// lst_utils
t_env			*ft_lstnew(char *content);

// main
void			print_error(t_token *token, unsigned int n);

// malloc_utils
char			*ft_strcpy(char *str1);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin2(char *str1, char *str2);
char			**array_cpy(char **arr);

// pars_utils
void			erased_str(t_token *token, unsigned int *s);
void			erased_str2(t_token *token, unsigned int s);
void			get_type(t_token *token, unsigned int one, unsigned int two);

// parsing
unsigned int	parsing(t_token *token, unsigned int *exit_stat);

// quotes_pars
void			erased_quote(t_token *token, unsigned int *p);
int				secnd_quote(t_token *token, unsigned int *one, t_type quote);
void			realloc_word(t_token *token, unsigned int *one,
					unsigned int two);

// str_utils
unsigned int	ft_strlen(char *str);
unsigned int	is_sep(char c);
unsigned int	wich_type(char c);
unsigned int	ft_strcmp(char *str, char *str2);

// transfert
void		    transfert(t_token *token, t_cmd *cmd);

// exec
void			parsing_exec(t_token *token, unsigned int *i);
void			exec(t_token *token, unsigned int *i);
void			cd(t_token *token, unsigned int *i);
void			pwd(t_token *token, unsigned int *i);
void			export(t_token *token, unsigned int *i);
void			unset(t_token *token, unsigned int *i);
void			exec_env(t_token *token);
void			echo(t_token *token, unsigned int *i);
void			env(t_token *token, unsigned int *i);
int				exitmentioned(t_token *token);
