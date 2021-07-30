#include "../../includes/minishell.h"

extern t_conf	g_sh;

int	exists_opt(int i, char **tmp)
{
	int	j;

	j = 1;
	if (tmp[i][j] == '-')
		return (0);
	else
	{
		while (tmp[i][j])
		{
			if (tmp[i][j] == 'n')
				j++;
			else
				return (0);
		}
	}
	return (j);
}

void	is_env(char *tmp)
{
	char	*e_val;

	e_val = search_env_value((tmp + 1), g_sh.env);
	if (ft_strchr(tmp, '$') && !(ft_strchr(tmp, '?')))
	{
		if (!(e_val))
			return ;
		else
			printf("%s", e_val);
	}
	else
		printf("%s", tmp);
}

void	do_echo(int i, char **tmp, t_blt *blt)
{
	char	*d_tmp;
	char	*s_tmp;

	while (tmp[i])
	{
		if (ft_strchr(tmp[i], '"'))
		{
			d_tmp = ft_strtrim(tmp[i], "\"");
			is_env(d_tmp);
			free(d_tmp);
		}
		else if (ft_strchr(tmp[i], '\''))
		{
			s_tmp = ft_strtrim(tmp[i], "'");
			printf("%s", s_tmp);
			free(s_tmp);
		}
		else
			is_env(tmp[i]);
		if (tmp[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!(blt->opt))
		printf("\n");
}

int	is_up_flag(char **tmp, t_blt *blt)
{
	int	i;

	i = 0;
	if (!(blt->up_flag))
	{
		while (tmp[i][0] == '-')
		{
			if (exists_opt(i, tmp))
				blt->opt = 1;
			else
				break ;
			i++;
		}
	}
	else if (!(ft_strncmp(tmp[i], "-n", ft_strlen(tmp[i]))))
	{
		blt->opt = 1;
		i++;
	}
	return (i);
}

void	run_echo(char *b_args, t_blt *blt)
{
	int		i;
	char	**tmp;

	if (b_args == NULL)
	{
		printf("\n");
		exit(0);
	}
	tmp = ft_split(b_args, ' ');
	i = is_up_flag(tmp, blt);
	do_echo(i, tmp, blt);
	ft_free_double((void **)tmp);
}
