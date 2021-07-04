#include "pipe.h"

void	parse_init(t_all *all)
{
	all->parse.p_cmd = NULL;
	all->parse.opt = 0;
	all->parse.args = NULL;
}

int		main(int ac, char **av, char **path)
{
	int		i;
	int		ret;
	char	*cwd;
	char	**dir;
	char	buf[BUFFER_SIZE];
	t_all	all;

	if (ac == 1)
	{
		printf("args are noting\n");
		exit(0);
	}
	parse_init(&all);
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
		// set environment variable
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
				printf("errno >> %d: No such file or directory\n", errno);
			else if (!(ret))
			{
				printf("chdir >> %d\n", ret);
				getcwd(buf, BUFFER_SIZE);
				printf("path >> %s\n", buf);
			}
		}
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "pwd", ft_strlen(all.parse.p_cmd)))) // set capital
	{
		cwd = getcwd(NULL, BUFFER_SIZE);
		printf("%s\n", cwd);
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "export", ft_strlen(all.parse.p_cmd))))
	{
	}
/*	else if (!(ft_strncmp(all.parse.p_cmd, "unset", ft_strlen(all.parse.p_cmd))))
	{
	}
	else if (!(ft_strncmp(all.parse.p_cmd, "env", ft_strlen(all.parse.p_cmd)))) // set capital
	{
	}*/
	return (0);
}
