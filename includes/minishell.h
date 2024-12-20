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

typedef struct token
{
	char			**word;
	unsigned int	*token;
}	t_token;

void			print_token(t_token *token);

unsigned int	ft_strcmp(char *str, char *str2);
void			parsing(t_token *token, char *input);
unsigned int	count_word(char *str);
unsigned int	ft_strlen(char *str);
unsigned int	malloc_word(t_token *token, char *input, unsigned int c);
