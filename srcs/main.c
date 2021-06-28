#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char **g_env = NULL;

void		show_prompt(void)
{
	ft_putstr_fd(COLOR_BR_BLUE, STDOUT);
	ft_putstr_fd("jaekpark's minishell", 1);
	ft_putstr_fd(COLOR_WHITE, STDOUT);
	ft_putstr_fd("$ ", STDOUT);
}

int			get_command_line(char **input)
{
	int		ret;
	char	*input2;
	char	*tmp;

	*input = ft_strdup("");
	while (TRUE)
	{
		ret = get_next_line(STDIN, &input2);
		tmp = ft_strjoin(*input, input2);
		free(input2);
		free(*input);
		*input = tmp;
		if (ret == 0)
		{
			ft_putstr_fd("  \b\b", STDOUT);
			if (ft_strlen(*input) != 0)
				continue;
			ft_putstr_fd("exit\n", STDOUT);
		}
		break ;
	}
	return (ret);
}

int main(int ac, char **av, char **envp)
{
	static char *input;
	int ret;

	(void)av;
	g_env = envp;
	ret = ac;
	while(ret)
	{
		show_prompt();
		readline(input);
		if (input != NULL)
			free(input);
	}

}
