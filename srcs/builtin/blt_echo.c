#include "../../includes/minishell.h"

int	exists_opt(int i, char **av)
{
	int	j;

	if (av[i][0] != '-')
		return (0);
	else
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'n')
				j++;
			else
				return (0);
		}
	}
	return (j);
}

void		run_echo(t_blt *blt)
{
	/*
	 *int	i;
	 */

	char **args = ft_split(blt->args, ' ');
	printf("opt >> |%s|\n", args[0]);
	printf("opt >> |%s|\n", args[1]);
	/*
	 *if (blt->opt)
	 *    i = 2;
	 *else
	 *    i = 1;
	 *if (!(blt->up_flag)) // all lower
	 *{
	 *    while (av[++i][0] == '-')
	 *    {
	 *        if (exists_opt(i, av))
	 *            all->blt.opt = 1;
	 *        else
	 *            break ;
	 *    }
	 *}
	 *else if (!(ft_strncmp(av[2], "-n", ft_strlen(av[2])))) // exists upper
	 *{
	 *    if (ft_strncmp(av[3], "-n", ft_strlen(av[3])))
	 *        i++;
	 *}
	 *if (i == 1)
	 *    i++;
	 *printf("here >> %d\n", i);
	 *while (av[i])
	 *{
	 *    printf("%s", av[i]);
	 *    i++;
	 *}
	 *if (!(all->blt.opt))
	 *    printf("\n");
	 */
	// undo: input space when ac > 3 // from jaekpark
	// undo: echo '$PATH' >> show PATH's value // from jaekpark
}
