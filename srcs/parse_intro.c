#include "../includes/pipe.h"

void	parse_init(t_all *all)
{
	all->parse.p_cmd = NULL;
	all->parse.opt = 0;
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

void	add_node_back(t_env **env, t_env *new) // **env == existing node
{
	t_env	*node;

	if (!(new) || !(*env))
		return ;
	node = *env;
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node; 
	new->next = NULL;
}

void	remove_node(t_env **env, char *target)
{
	t_env	*node;

	if (!(target))
		return ;
	node = *env;
	if (!(ft_strncmp(node->key, target, ft_strlen(node->key)))) // head
	{
		node->next->prev = NULL;
		return ;
	}
	while (node->next) // middle
	{
		if (!(ft_strncmp(node->key, target, ft_strlen(node->key))))
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			return ;
		}
		node = node->next;
	}
	if (!(ft_strncmp(node->key, target, ft_strlen(node->key)))) // tail
		node->prev->next = NULL;
	return ;
}

int		main(int ac, char **av, char **path)
{
	int		i;
	int		ret;
	int		e_flag;
	char	*cwd;
	char	**dir;
	char	**in_tmp;
	char	**ex_tmp;
	char	buf[BUFFER_SIZE];
	t_all	all;

	if (ac == 1)
	{
		printf("args are noting\n");
		exit(0);
	}
	parse_init(&all);
	all.env = *env_init(&all.env);
	all.parse.p_cmd = av[1];
	if (!(ft_strncmp(all.parse.p_cmd, "echo", ft_strlen(all.parse.p_cmd)))) // set capital
	{
		if (!(ft_strncmp(av[2], "-n", ft_strlen(av[2]))))
		{
			all.parse.opt = 1;
			i = 2;
		}
		else
			i = 1;
		while (av[++i])
			printf("%s", av[i]);
		if (!(all.parse.opt))
			printf("\n");
		// set environment variable : echo $PATH >> show PATH's value
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "cd", ft_strlen(all.parse.p_cmd))))
	{
		if (!(av[2])) // $HOME
		{
			i = -1;
			while (path[++i])
			{
				if (!(ft_strncmp(path[i], "HOME", 4)))
				{
					dir = ft_split(path[i], '=');
					printf("%s\n", dir[1]);
				}
			}
		}
		else
		{
			ret = chdir(av[2]);
			if (ret == -1)
				printf("%s\n", strerror(errno));
			else if (!(ret))
			{
				printf("chdir >> %d\n", ret);
				getcwd(buf, 0);
				printf("path >> %s\n", buf);
			}
		}
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "pwd", ft_strlen(all.parse.p_cmd)))) // set capital
	{
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "export", ft_strlen(all.parse.p_cmd))))
	{
		if (!(av[2]))
		{
			e_flag = 1;
			while (*path) // call env func
			{
				printf("declare -x %s\n", *path);
				path++;
			}
		}
		else // lst_addback
		{
			in_tmp = ft_split(av[2], '=');
			while (*path)
			{
				ex_tmp = ft_split(*path, '=');
				all.env.key = ex_tmp[0];
				all.env.value = ex_tmp[1];
				if (!(ft_strncmp(*path, in_tmp[0], 4))) // key is already exists
				{
					all.env.value = in_tmp[1];
					return (0);
				}
				path++;
			}
			//	add_node_back(all.env, new); // add new key=value
		}
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "unset", ft_strlen(all.parse.p_cmd))))
	{
		while (*path)
		{
			if (!(ft_strncmp(*path, av[2], 4)))
			{
			//	remove_node(all.env, target);
				printf(">> %s\n", *path);
			}
			path++;
		}
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "env", ft_strlen(all.parse.p_cmd)))) // set capital
	{
		e_flag = 0;
		while (*path)
		{
			if (e_flag == 1)
				printf("declare -x %s\n", *path);
			else
				printf("%s\n", *path);
			path++;
		}
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "exit", ft_strlen(all.parse.p_cmd))))
	{
		printf("exit\n");
		printf("\n");
		exit(0);
	}
	return (0);
}
