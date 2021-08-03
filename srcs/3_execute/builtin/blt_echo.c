#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	exists_opt(int i, char **tmp)
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

void	do_echo(int i, char **tmp, t_blt *blt)
{
	while (tmp[i])
	{
		printf("%s", tmp[i]);
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

void	run_echo(t_cmd *proc, t_blt *blt)
{
	int		i;
	char	**tmp;

	if (proc->arg == NULL)
	{
		printf("\n");
		return ;
	}
	tmp = ft_split(proc->arg, ' ');
	i = is_up_flag(tmp, blt);
	do_echo(i, tmp, blt);
	ft_free_double((void **)tmp);
}
