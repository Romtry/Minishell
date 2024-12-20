#include "minishell.h"

void	print_token(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		printf("word %u = [%s]\n", i, token->word[i]);
		i++;
	}
}
