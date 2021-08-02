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

/*
 *void	is_env(char *tmp)
 *{
 *    char	*e_val;
 *
 *    e_val = search_env_value((tmp + 1), g_sh.env);
 *    printf("tmp is %s\n", tmp);
 *    if (ft_strchr(tmp, '$') && !(ft_strchr(tmp, '?')))
 *    {
 *        printf("here\n");
 *        if (!(e_val))
 *            return ;
 *        else
 *            printf("%s", e_val);
 *    }
 *    else
 *        printf("%s", tmp);
 *}
 */

void	do_echo(int i, char **tmp, t_blt *blt)
{
	/*
	 *char	*d_tmp;
	 *char	*s_tmp;
	 */

	while (tmp[i])
	{
		printf("%s", tmp[i]);
		int j = exists_opt(i, tmp);
		printf("j is %d\n", j);
		/*
		 *if (ft_strcmp(tmp[i], "$#") == 0)
		 *    printf("%c", '0');
		 */

		/*
		 *if (ft_strchr(tmp[i], '"'))
		 *{
		 *    d_tmp = ft_strtrim(tmp[i], "\"");
		 *    printf("d_tmp is %s\n", d_tmp);
		 *    is_env(d_tmp);
		 *    free(d_tmp);
		 *}
		 *else if (ft_strchr(tmp[i], '\''))
		 *{
		 *    s_tmp = ft_strtrim(tmp[i], "'");
		 *    printf("s: %s", s_tmp);
		 *    free(s_tmp);
		 *}
		 *printf("%s", tmp[i]);
		 */
		/*
		 *printf("%s", s_tmp)
		 */
		/*
		 *else
		 *    is_env(tmp[i]);
		 */
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

	int j = -1;
	while (tmp[++j])
	{
		printf("tmp is %s\n", tmp[j]);
	}
	i = 0;
	if (!(*tmp))
		return (0);
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
		return ;
	}
	// not  exist -n
	printf("%s\n", b_args);
	printf("flag is %d\n", blt->up_flag);
	tmp = ft_split(b_args, ' ');
	i = is_up_flag(tmp, blt);
	printf("i is %d\n", i);
	do_echo(i, tmp, blt);
	ft_free_double((void **)tmp);
}
