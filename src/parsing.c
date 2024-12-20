#include "minishell.h"

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->word = malloc(sizeof(char **) * (count_word(input) + 1));
	while (c < count_word(input))
	{
		i += malloc_word(token, input + i, c);
		c++;
	}
	token->word[c] = NULL;
	print_token(token);
}

void	parsing(t_token *token, char *input)
{
	lexer(token, input);
}
