#include "../../includes/minishell.h"

extern t_conf g_sh;

int		exists_opt(int i, char **tmp)
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

void	is_env(char *tmp, t_env *env)
{
	char *e_val;

	(void)env;
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

void	do_echo(int i, char **tmp, t_blt *blt, t_env *env)
{
	char	*d_tmp;
	char	*s_tmp;

	while (tmp[i])
	{
		if (ft_strchr(tmp[i], '"'))
		{
			d_tmp = ft_strtrim(tmp[i], "\"");
			is_env(d_tmp, env);
			free(d_tmp);
		}
		else if (ft_strchr(tmp[i], '\''))
		{
			s_tmp = ft_strtrim(tmp[i], "'");
			printf("%s", s_tmp);
			free(s_tmp);
		}
		else
			is_env(tmp[i], env);
		if (tmp[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!(blt->opt))
		printf("\n");
}

void	run_echo(t_blt *blt, t_env *env)
{
	int		i;
	char	**tmp;

	if (blt->args == NULL)
	{
		printf("\n");
		return ;
	}
	tmp = ft_split(blt->args, ' ');
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
	do_echo(i, tmp, blt, env);
	int j = 0;
	while (tmp[j])
	{
		free(tmp[j]);
		j++;
	}
	free(tmp);
}
