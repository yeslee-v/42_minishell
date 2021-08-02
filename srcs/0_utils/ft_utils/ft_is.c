#include "../../../includes/minishell.h"

int	ft_isspec(char *cmd, int i)
{
	int	last;

	last = 0;
	if (cmd[i + 1] == '\0')
		last = 1;
	if (cmd[i] == '|')
		return (1);
	else if (last != 1 && (ft_strncmp(&cmd[i], "<<", 2)) == 0)
		return (2);
	else if (last != 1 && (ft_strncmp(&cmd[i], ">>", 2)) == 0)
		return (3);
	else if (cmd[i] == '<')
		return (4);
	else if (cmd[i] == '>')
		return (5);
	return (0);
}

int	ft_isspace(int c)
{
	if ((char)c == ' ')
		return (1);
	else if ((char)c == '\t')
		return (2);
	else if ((char)c == '\v')
		return (3);
	else if ((char)c == '\n')
		return (4);
	else if ((char)c == '\f')
		return (5);
	else if ((char)c == '\r')
		return (6);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == 34)
		return (68);
	else if (c == 39)
		return (81);
	return (0);
}
