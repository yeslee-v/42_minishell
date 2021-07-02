#include "pipe.h"

void	parse_init(t_parse *parse)
{
	parse->p_cmd = NULL;
	parse->opt = 0;
	parse->args = NULL;
}

int		main(int ac, char **av)
{
	int		i;
	t_parse	parse;

	parse_init(&parse);
	i = -1;
	while (av[++i])
		printf("ac >> %d av[%d] >> %s\n", ac, i, av[i]);
	
	if (!(ft_strncmp(av[2], "-n", ft_strlen(av[2]))))
	{
		parse.opt = 1;
		printf("flag is %d >> it has '-n'\n", parse.opt);
	}
	else
	{
		int j = -1;
		while (av[2][++j])
		{
			printf("deeper >> %c\n", av[2][j]);
		}
		printf("flag error");
	}
	return (0);
}
