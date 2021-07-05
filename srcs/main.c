/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/05 20:56:26 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/fcntl.h>

t_conf	g_sh;

void	print_env(t_lst *env)
{
	t_env	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("==============================\n");
		printf("key = %s\nvalue = %s\n", tmp->key, tmp->value);
		printf("==============================\n");
		tmp = tmp->next;
	}
}

void	exit_shell(int num)
{
	printf("Good bye ~ !\n");
	exit(num);
}

void	print_token(t_lst *token)
{
	t_token	*temp;

	temp = token->head;
	while (temp)
	{
		printf("token = %s, type = %c, index = %d, st = %d, ed = %d\n",
				temp->token,
				temp->type,
				temp->i,
				temp->st,
				temp->ed);
		temp = temp->next;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_terminal(void)
{
	tcgetattr(0, &g_sh.term);
	g_sh.term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g_sh.term);
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*void	parser(t_lst *token)*/
/*{*/
	/*int		syntax;*/
	/*t_token	*tmp;*/
	/*char	*cmd;*/
	/*char	*arg;*/

	/*syntax = 0;*/
	/*tmp = token->head;*/
	/*while (tmp)*/
	/*{*/
		/*if (syntax == 0 && tmp->i == 0)*/
		/*{*/
			/*cmd = ft_strdup(tmp->token);*/
			/*syntax++;*/
		/*}*/
		/*else if (tmp->i >= 1)*/
		/*{*/
			/*if (arg == NULL)*/
				/*arg = ft_strdup(tmp->token);*/
			/*else*/
				/*arg = ft_strjoin_sp(arg, tmp->token);*/
		/*}*/
		/*else if (syntax == 1 && tmp->i == 0)*/
			/*make_syntax(cmd, arg);*/
		/*tmp = tmp->next;*/
	/*}*/
/*}*/

void	set_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	rl_redisplay();
	lexer(g_sh.cmd);
	tokenizer(&g_sh, g_sh.lexer->lex);
	printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lexer->lex);
	print_token(g_sh.token);
	if ((ft_strcmp(g_sh.cmd, "exit")) == 0)
		exit_shell(0);
	if (g_sh.lexer->err == 1)
		printf("quote err\n");
	free(g_sh.cmd);
	free_lexer(g_sh.lexer);
}

char	**split_env(char *env)
{
	char	**ret;
	int		i;

	i = -1;
	if (!env)
		return (NULL);
	ret = malloc(sizeof(char *) * 3);
	while (env[++i])
	{
		if (env[i] == '=' && env[i + 1] != '\0')
		{
			ret[0] = ft_strrdup(env, 0, i - 1);
			ret[1] = ft_strrdup(env, i + 1, ft_strlen(env) - 1);
			ret[2] = NULL;
			break ;
		}
		else if (env[i] == '=' && env[i + 1] == '\0')
		{
			ret[0] = ft_strrdup(env, 0, i - 1);
			ret[1] = NULL;
			ret[2] = NULL;
			break ;
		}
	}
	return (ret);
}

void	set_env(char **envp)
{
	int		i;
	char	**tmp;
	t_lst	*env;

	i = -1;
	tmp = NULL;
	env = malloc(sizeof(t_lst));
	init_lst(env);
	while (envp[++i])
	{
		tmp = split_env(envp[i]);
		make_env(env, tmp[0], tmp[1]);
	}
	g_sh.env = env;
}

/*void	set_logo(void)*/
/*{*/
/*char *logo;*/
/*int ret;*/
/*int fd;*/

/*ret = 0;*/
/*logo = NULL;*/
/*fd = open("/Users/jaekpark/jaekpark_42cursus/minishell/srcs/b.txt", O_RDONLY);*/
/*printf("fd = %d\n", fd);*/
/*while ((ret = get_next_line(fd, &logo)) >= 0)*/
/*{*/
/*printf("%s", logo);*/
/*free(logo);*/
/*if (ret == 0)*/
/*break ;*/
/*}*/
/*}*/

int		main(int ac, char **av, char **envp)
{
	int	ret;

	(void)av;
	ret = ac;
	set_env(envp);
	set_terminal();
	while (ret)
	{
		set_signal();
		set_prompt();
	}
}
