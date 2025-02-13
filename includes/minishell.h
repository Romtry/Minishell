/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:34:49 by ttouahmi          #+#    #+#             */
/*   Updated: 2025/02/12 14:30:23 by rothiery         ###   ########.fr       */
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
#include <stdbool.h>

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
	t_type			**type;
	char			***word;
	unsigned int	has_pipe;
	unsigned int	*exit_stat;
}	t_cmd;

typedef struct token
{
	unsigned int	err;
	unsigned int	tlen;
	t_env			*envhead;
	char			**word;
	t_type			*type;
	unsigned int	exit_stat;
}	t_token;

// main
void			print_error(t_token *token, unsigned int n);
void 				*get_env(bool b);

// test
void				print_array(char **array);
void				print_token(t_token *token);
void				print_cmd(t_cmd *cmd);

// exec
// bultin
void				cd(t_cmd *cmd);
void				echo(t_cmd *cmd);
void				env_builtin(void);
void				exit_shell(t_cmd *cmd);
void				ft_export(t_cmd *cmd);
void				pwd(void);
int					handle_redirections(t_cmd *cmd);
void				unset(t_cmd *cmd);

// env_exec
t_env 				**get_env_head(void);
void 				remove_duplicates_from_environ(void);
void 				sync_env_with_system(void);

// utils
int 				cmd_count(t_cmd *cmd);
void				execute_builtin(t_cmd *cmd);
void				execute_command(t_cmd *cmd);
char 				*get_command_path(char *cmd);
void				execute_external(t_cmd *cmd);
void				execute_piped_commands(t_cmd *cmd);

// fonc_utils
// comp
unsigned int		ft_strcmp(char *str, char *str2);
unsigned int		ft_strncmp(char *str, char *str2, unsigned int n);
int					is_builtin(char *cmd);
unsigned int		is_sep(char c);
unsigned int		wich_type(char c);

// lst
t_env				*ft_lstnew(char *content);
char				*get_name(char const *content, unsigned int *i);

// str
char				**array_cpy(char **arr);
void				erased_str(t_token *token, unsigned int *s);
void				erased_str2(t_token *token, unsigned int s);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				**ft_split(const char *str, char target);
char 				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *str1);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char *s1, char *s2, bool b);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
unsigned int		ft_strlen(const char *str);
char				*ft_strndup(const char *s, size_t n);

// free_utils
void				free_array(char **arr);
void				free_cmd(t_cmd	*cmd);
void				free_env(t_env *env);
void				free_token(t_token *token);
void				free_word(t_token *token);
void				print_cmd(t_cmd *cmd);


// parsing_part
// lexer_utils
void				lexer(t_token *token, char *input);
unsigned int		malloc_word(t_token *token, char *input, unsigned int c);
unsigned int		tlen_count(char *str);

// parsing
// dollar_utils
char				*num_char(unsigned int n);
void				pars_dollar(t_token *token, unsigned int i);
void				switch_dollar(t_token *token, unsigned int one, unsigned int *two);
void				switch_es(t_token *token, unsigned int i);
void			    transfert(t_token *token, t_cmd	*cmd);

// quote_utils
void				dollar_indquote(t_token *token, unsigned int *one, unsigned int *two);
void				erased_quote(t_token *token, unsigned int *p);
void				quote_type(t_token *token, unsigned int one, unsigned int *temp);
void				realloc_word(t_token *token, unsigned int *one, unsigned int two);
int					secnd_quote(t_token *token, unsigned int *one, t_type quote);

// utils
void				dollar_pars(t_token *token, unsigned int *i);
void				dollar_quote(t_token *token, unsigned int i);
void				get_type(t_token *token, unsigned int one, unsigned int two);
unsigned int		parsing(t_token *token);
void				pipe_pars(t_token *token, unsigned int i);
void				redir_pars(t_token *token);
void				sep_clean(t_token *token);

// transfert_utils
void				malloc_array(t_token *token, t_cmd *cmd);
void				no_pipe(t_token *token, t_cmd *cmd);
void				transfert_pipe(t_cmd *cmd, unsigned int *p, unsigned int *i2);
void			    transfert(t_token *token, t_cmd	*cmd);
