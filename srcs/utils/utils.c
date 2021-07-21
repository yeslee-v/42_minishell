#include "../../includes/minishell.h"

int		get_redir_fd(char *cmd)
{
	int i;
	int fd;

	i = -1;
	fd = 0;
	if (!cmd || (ft_strlen(cmd)) >= 6)
		return (-1);
	while (cmd[++i])
	{
		printf("%c\n", cmd[i]);
		if ((ft_isnum(cmd[i])) == 1)
			fd = (fd * 10) + (cmd[i] - '0');
		else
			break ;

	}
	if (fd > 255 || fd < 0)
		return (-1);
	return (fd);
}
