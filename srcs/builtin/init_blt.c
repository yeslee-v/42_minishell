#include "../../includes/minishell.h"

void	init_blt(t_all *all)
{
	all->blt.p_cmd = NULL;
	all->blt.opt = 0;
	all->blt.up_flag = 0;
	all->blt.args = NULL;
}

t_env *init_env(t_env *env) // be deleted when merge
{
	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}

void	set_lower(char *cmd, t_all *all)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] >= 65) && (cmd[i] <= 90))
		{
			cmd[i] += 32;
			all->blt.up_flag = 1;
		}
		i++;
	}
}

void	set_builtin(t_all *all, int ac, char **av, char **path)
{
	if (!(ft_strncmp(all->blt.p_cmd, "echo", ft_strlen(all->blt.p_cmd))))
		run_echo(av, all);
	else if (!(ft_strncmp(all->blt.p_cmd, "cd", ft_strlen(all->blt.p_cmd))))
		run_cd(av, path, all);
	else if (!(ft_strncmp(all->blt.p_cmd, "pwd", ft_strlen(all->blt.p_cmd))))
		run_pwd();
	else if (!(ft_strncmp(all->blt.p_cmd, "export", ft_strlen(all->blt.p_cmd))))
		run_export(av, path, all);
	else if (!(ft_strncmp(all->blt.p_cmd, "unset", ft_strlen(all->blt.p_cmd))))
		run_unset(ac, av, path, all);
	else if (!(ft_strncmp(all->blt.p_cmd, "env", ft_strlen(all->blt.p_cmd))))
		run_env(path);
	else if (!(ft_strncmp(all->blt.p_cmd, "exit", ft_strlen(all->blt.p_cmd))))
		run_exit(all);
}

int		intro_blt_intro(int ac, char **av, char **path)
{
	t_all	all;

	init_blt(&all);
	all.env = *init_env(&all.env);
	all.blt.p_cmd = av[1];
	set_lower(all.blt.p_cmd, &all);
	set_builtin(&all, ac, av, path);
	return (0);
}
