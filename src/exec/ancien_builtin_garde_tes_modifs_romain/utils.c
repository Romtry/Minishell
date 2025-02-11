# include "minishell.h"

int	char_int(char *str)
{
	int				ret;
	int				temp;
	int				signe;
	unsigned int	i;

	ret = 0;
	signe = 1;
	i = 0;
	if (str[0] == '-')
		signe = -1;
	while (str[i])
	{
		temp = str[i] - '0';
		ret = ret * 10;
		ret = ret + temp;
		i++;
	}
	ret = ret * signe;
	return (ret);
}

static int	count_words(const char *str, char target)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == target)
		{
			i++;
		}
		if (str[i] && str[i] != target)
		{
			count++;
		}
		while (str[i] && str[i] != target)
		{
			i++;
		}
	}
	return (count);
}

static char	*grab_words(const char *str, char target, int reset)
{
	static int	i = 0;
	int			j;
	char		*word;

	j = 0;
	if (!reset)
	{
		while (str[i] && str[i] == target)
			i++;
		while (str[i + j] && str[i + j] != target)
			j++;
		word = malloc(sizeof(char) * (j + 1));
		j = 0;
		while (str[i] && str[i] != target)
		{
			word[j] = str[i];
			j++;
			i++;
		}
		word[j] = '\0';
		return (word);
	}
	i = 0;
	return (NULL);
}

char	**ft_split(const char *str, char target)
{
	int		i;
	int		count;
	char	**ret;

	i = 0;
	count = count_words(str, target);
	ret = malloc(sizeof(char *) * (count + 1));
	if (ret == NULL)
	{
		return (NULL);
	}
	while (count > 0)
	{
		ret[i] = grab_words(str, target, 0);
		i++;
		count--;
	}
	ret[i] = grab_words(str, target, 1);
	return (ret);
}
