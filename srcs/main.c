#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_conf	g_sh;

void	exit_shell(int num)
{
	printf("Good bye ~ !\n");
	exit(num);
}

void	test_print(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int print_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	if (g_sh.cmd != NULL)
		free(g_sh.cmd);
	return (1);
}

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("\b", 0);
		rl_redisplay();
	}
}

int		main(int ac, char **av, char **envp)
{
	int	ret;
	char *input;

	(void)av;
	ret = ac;
	g_sh.env = envp;
	test_print(g_sh.env);
	while (ret)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline(PROMPT);
		if (input == NULL)
			exit(0);
		if ((ft_strcmp(input, "exit")) == 0)
			exit_shell(0);
//check_eof(input);
		add_history(input);
		free(input);
	}
}
