#include "../../includes/minishell.h"

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

void	run_echo(t_blt *blt)
{
	int		i;
	char	**tmp;

	tmp = ft_split(blt->args, ' ');
	i = 0;
	if (!(blt->up_flag)) // all lower
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
	else if (!(ft_strncmp(tmp[i], "-n", ft_strlen(tmp[i])))) // exists upper
	{
		blt->opt = 1;
		i++;
	}
	while (tmp[i])
	{
		printf("%s", tmp[i]);
		if (tmp[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!(blt->opt))
		printf("\n");
	// undo: echo '$PATH' >> show PATH's value // from jaekpark
}
