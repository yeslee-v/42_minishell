#include "../includes/pipe.h"

void	parse_init(t_all *all)
{
	all->parse.p_cmd = NULL;
	all->parse.opt = 0;
	all->parse.up_flag = 0;
	all->parse.args = NULL;
}

t_env	*env_init(t_env *env)
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
	int i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] >= 65) && (cmd[i] <= 90))
		{
			cmd[i] += 32;
			all->parse.up_flag = 1;
		}
		i++;
	}
}

/*
 *int		blt_intro(int ac, char **av, char **path)
 */
int			main(int ac, char **av, char **path)
{
	/*
	 *int		e_flag;
	 */
	t_all	all;

	if (ac == 1)
	{
		printf("args are noting\n");
		exit(0);
	}
	parse_init(&all);
	all.env = *env_init(&all.env);
	all.parse.p_cmd = av[1];
	set_lower(all.parse.p_cmd, &all);
	if (!(ft_strncmp(all.parse.p_cmd, "echo", ft_strlen(all.parse.p_cmd)))) // set capital
		run_echo(av, &all);
	else if (!(ft_strncmp(all.parse.p_cmd, "cd", ft_strlen(all.parse.p_cmd))))
		run_cd(av, path, &all);
	else if (!(ft_strncmp(all.parse.p_cmd, "pwd", ft_strlen(all.parse.p_cmd)))) // set capital
		run_pwd();
	else if (!(ft_strncmp(all.parse.p_cmd, "export", ft_strlen(all.parse.p_cmd))))
		run_export(av, path, &all);
	else if (!(ft_strncmp(all.parse.p_cmd, "unset", ft_strlen(all.parse.p_cmd))))
		run_unset(ac, av, path, &all);
	else if (!(ft_strncmp(all.parse.p_cmd, "env", ft_strlen(all.parse.p_cmd)))) // set capital
		run_env(path);
	else if (!(ft_strncmp(all.parse.p_cmd, "exit", ft_strlen(all.parse.p_cmd))))
		run_exit(&all);
	return (0);
}
