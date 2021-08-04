#include "../../includes/minishell.h"

extern t_conf	g_sh;

int	find_opt(int i, char **tmp)
{
	int	j;

	j = 1;
	if ((tmp[i][j] == '-') || !(tmp[i][j]))
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

int	do_calc(int i, char **tmp, t_blt *blt)
{
	int	ret;

	ret = 0;
	while (tmp[i])
	{
		ret += ft_strlen(tmp[i]);
		if (tmp[i + 1] != NULL)
			ret += 1;
		i++;
	}
	if (blt->opt)
		return (ret);
	return (0);
}

int	set_up_flag(char **tmp, t_blt *blt)
{
	int	i;

	i = 0;
	if (!(blt->up_flag))
	{
		while (tmp[i] && (tmp[i][0] == '-'))
		{
			if (exists_opt(i, tmp))
				blt->opt = 1;
			else
				break ;
			i++;
		}
	}
	else if (ft_strcmp(tmp[i], "-n") == 0)
	{
		blt->opt = 1;
		i++;
	}
	return (i);
}

int	calc_echo(t_cmd *proc, t_blt *blt)
{
	int		ret;
	int		i;
	char	**tmp;

	if (proc->arg == NULL)
		return (0);
	tmp = ft_split(proc->arg, ' ');
	i = set_up_flag(tmp, blt);
	ret = do_calc(i, tmp, blt);
	ft_free_double((void **)tmp);
	return (ret);
}
