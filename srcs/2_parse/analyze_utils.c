#include "../../includes/minishell.h"

int	check_valid_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*get_env_in_cmd(char *str, char *lex)
{
	char	*ret;
	int		st;
	int		i;
	int		j;

	ret = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && lex[i] != 'q')
		{
			j = i;
			st = i;
			while (str[++j])
			{
				if ((check_valid_char(str[j])) == 0)
					break ;
			}
			if (st == j || st == j - 1)
				return (NULL);
			else
				return (ft_strrdup(str, st, j - 1));
		}
	}
	return (NULL);
}

int	get_arg_cnt(char *lex)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	if (!lex)
		return (-1);
	while (lex[++i])
	{
		if (ft_strchr("dqsc", lex[i]))
			cnt++;
	}
	return (cnt);
}

char	*strdup_only_char(char *lex, char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	if (!lex || !str)
		return (NULL);
	size = get_arg_cnt(lex);
	ret = malloc(sizeof(char) * (size + 1));
	while (lex[++i])
	{
		if (ft_strchr("dqsc", lex[i]))
		{
			ret[j] = str[i];
			j++;
		}
	}
	ret[size] = '\0';
	return (ret);
}

int	check_quote_exist(char *lex)
{
	int	i;

	i = 0;
	if (!lex)
		return (-1);
	while (lex[i])
	{
		if (ft_strchr("DQ", lex[i]))
			return (1);
		i++;
	}
	return (0);
}
