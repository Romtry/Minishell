/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:34:49 by ttouahmi          #+#    #+#             */
/*   Updated: 2025/03/16 12:08:53 by rothiery         ###   ########.fr       */
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
#define CLEAR		"\e[0m\n"
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
	t_type					**type;
	unsigned int			exit;
	t_env					**env_head_ptr;
	char					***word;
	unsigned int			has_pipe;
	unsigned int			*exit_stat;
	char					***old_environ;
	bool					*env_change;
	volatile sig_atomic_t	heredoc_interrupted;
	int						heredoc_fd;
}	t_cmd;

typedef struct token
{
	unsigned int	err;
	unsigned int	tlen;
	t_env			*envhead;
	char			**word;
	t_type			*type;
	unsigned int	*exit_stat;
	char			**old_environ;
	bool			env_change;
}	t_token;

void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);

// main
void				print_error(t_token *token, unsigned int n);
void				*get_env(bool b);
void				free_end(t_env *env, t_token *token);
void				handle_signal(int sig);

// test
void				print_array(char **array);
void				print_token(t_token *token);
void				print_cmd(t_cmd *cmd);
void				env_print(t_env *env);

// exec
void				handle_child(int i, t_cmd *cmd, int input_fd,
						int pipe_fd[2]);
void				var_work(t_cmd *cmd, char *name, char *value);
bool				var_init(t_cmd *cmd, char *name, char *value);
char				*get_command_path(char *cmd);

// bultin
void				cd(t_cmd *cmd);
char				*cd2(void);
void				echo(t_cmd *cmd);
void				env_builtin(t_cmd *cmd);
void				exit_shell(t_cmd *cmd);
void				ft_export(t_cmd *cmd);
void				pwd(t_cmd *cmd);
int					handle_redirections(t_cmd *cmd);
void				unset(t_cmd *cmd);
void				determine_redirection_params(int append, int *flags,
						const char **redir_type);
int					process_redir(t_cmd *cmd, int *i, int *j, char **new_args);
void				read_heredoc_lines(t_cmd *cmd,
						int pipe_fd, char *delimiter);
int					handle_fd_dup(int fd, int std_fd);
int					handle_heredoc(t_cmd *cmd, char *delimiter);

// redir.c
int					handle_out_redir(t_cmd *cmd, int *i);
int					handle_heredoc_redir(t_cmd *cmd, int *i, int k);
int					handle_in_redir(t_cmd *cmd, int *i);
int					handle_out_redir(t_cmd *cmd, int *i);
int					end_func(t_cmd *cmd, char **new_args, int j, int k);

// env_exec
t_env				**get_env_head(void);
void				sync_env_with_system(t_cmd *cmd);

// utils
int					cmd_count(t_cmd *cmd);
void				execute_builtin(t_cmd *cmd);
void				execute_command(t_cmd *cmd, int i, int j, int k);
char				*get_command_path(char *cmd);
void				execute_external(t_cmd *cmd);
void				execute_piped_commands(t_cmd *cmd);

// fonc_utils
// comp
bool				ft_is_alnum(char c);
bool				ft_is_alpha(char c);
unsigned int		ft_strcmp(char *str, char *str2);
unsigned int		ft_strncmp(char *str, char *str2, unsigned int n);
int					is_builtin(char *cmd);
unsigned int		is_sep(char c);
unsigned int		wich_type(char c);

// lst
t_env				*ft_lstnew(char *content);
char				*get_name(char const *content, unsigned int *i);

// str
int					count_args(char **args);
char				**array_cpy(char **arr);
void				erased_str(t_token *token, unsigned int *s);
void				erased_str2(t_token *token, unsigned int s);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				**ft_split(const char *str, char target);
char				*ft_strchr(const char *s, int c);
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
void				dollar_pars(t_token *token, unsigned int *i);
char				*num_char(unsigned int n);
void				pars_dollar(t_token *token, unsigned int i);
void				switch_dollar(t_token *token, unsigned int one,
						unsigned int *two);
void				switch_es(t_token *token, unsigned int i);
void				transfert(t_token *token, t_cmd	*cmd);

// quote_utils
void				dollar_indquote(t_token *token, unsigned int *one,
						unsigned int *two);
void				dollar_quote(t_token *token, unsigned int i);
void				erased_quote(t_token *token, unsigned int *p);
void				quote_type(t_token *token, unsigned int one,
						unsigned int *temp);
void				realloc_word(t_token *token, unsigned int *one,
						unsigned int two);
void				secnd_quote(t_token *token, unsigned int *one,
						t_type quote);

// utils
void				get_type(t_token *token, unsigned int one,
						unsigned int two);
void				pars_heredoc(t_token *token, unsigned int i);
unsigned int		parsing(t_token *token);
void				pipe_pars(t_token *token, unsigned int i);
void				redir_pars(t_token *token);
void				sep_clean(t_token *token);

// transfert_utils
void				malloc_array(t_token *token, t_cmd *cmd);
void				no_pipe(t_token *token, t_cmd *cmd);
void				transfert_pipe(t_cmd *cmd, unsigned int *p,
						unsigned int *i2);
void				transfert(t_token *token, t_cmd	*cmd);
