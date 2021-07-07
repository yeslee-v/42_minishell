/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/07 18:44:41 by parkjaekw        ###   ########.fr       */
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
		printf("token = %s, type = %c, index = %d, st = %d, ed = %d, next = "
				"%p\n",
				temp->token,
				temp->type,
				temp->i,
				temp->st,
				temp->ed,
				temp->next);
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

void	make_syntax(t_lst *lst, char *cmd, char *arg)
{
	t_syntax	*tmp;
	t_syntax	*node;

	node = malloc(sizeof(t_syntax));
	node->cmd = ft_strdup(cmd);
	node->arg_line = ft_strdup(arg);
	node->arg_word = NULL;
	node->next = NULL;
	node->prev = NULL;
	if (lst->head == NULL && lst->tail == NULL)
	{
		lst->head = node;
		lst->tail = node;
	}
	else if (lst->head != NULL && lst->tail != NULL)
	{
		tmp = lst->tail;
		node->prev = tmp;
		tmp->next = node;
		lst->tail = node;
	}
	if (cmd != NULL)
		free(cmd);
	if (arg != NULL)
		free(arg);
}

void	save_process(t_lst *lst, t_lst *syntax)
{
	t_process	*tmp;
	t_process	*node;

	node = malloc(sizeof(t_process));
	node->syntax = syntax;
	node->next = NULL;
	node->prev = NULL;
	if (lst->head == NULL && lst->tail == NULL)
	{
		lst->head = node;
		lst->tail = node;
	}
	else if (lst->head != NULL && lst->tail != NULL)
	{
		tmp = lst->tail;
		node->prev = tmp;
		tmp->next = node;
		lst->tail = node;
	}
}

void	print_syntax(t_lst *syntax)
{
	t_syntax	*tmp;

	tmp = syntax->head;
	while (tmp)
	{
		printf("cmd = %s, arg = %s\n", tmp->cmd, tmp->arg_line);
		tmp = tmp->next;
	}
}

void	print_process(t_lst *process)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = process->head;
	while (tmp)
	{
		printf("process no.%d\n", i);
		printf("next = %p\n", tmp->next);
		print_syntax(tmp->syntax);
		i++;
		tmp = tmp->next;
	}
}

void	init_parse(t_parse *flag, int pipe)
{
	flag->start = 0;
	flag->pipe = 0;
	flag->cmd = NULL;
	flag->arg = NULL;
	if (flag->syntax == NULL || pipe == 1)
	{
		flag->syntax = malloc(sizeof(t_lst));
		init_lst(flag->syntax);
	}
}

t_token	 *parser(t_lst *process, t_token *tok)
{
	char *cmd_t;
	char *arg_t;
	t_lst *syn;

	(void)process;
	cmd_t = NULL;
	arg_t = NULL;
	syn = malloc(sizeof(t_lst));
	init_lst(syn);
	while (tok)
	{
		if (tok->i == 0 && tok->type == 'S')
			cmd_t = ft_strdup(tok->token);
		else if (tok->i >= 1 && tok->type == 'S')
			arg_t = ft_strjoin_sp(arg_t, tok->token);
		else if (tok->i == 0 && (ft_strchr("OIAH", tok->type)))
		{
			make_syntax(syn, cmd_t, arg_t);
			cmd_t = ft_strdup(tok->token);
			arg_t = NULL;
		}
		else if (tok->i == -1)
		{
			tok = tok->next;
			break ;
		}
		tok = tok->next;
	}
	if (cmd_t != NULL || arg_t != NULL)
		make_syntax(syn, cmd_t, arg_t);
	save_process(process, syn);
	return (tok);
}

void	set_prompt(void)
{
	t_token *tmp;

	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	rl_redisplay();
	lexer(g_sh.cmd);
	tokenizer(&g_sh, g_sh.lexer->lex);
	g_sh.process = malloc(sizeof(t_lst));
	init_lst(g_sh.process);
	tmp = g_sh.token->head;;
	while ((tmp = parser(g_sh.process, tmp)) != NULL)
		;
	if (tmp != NULL)
		parser(g_sh.process, tmp);
	printf("[lexical analysis]\n");
	printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lexer->lex);
	printf("------------------\n");
	printf("[tokenizing]\n");
	print_token(g_sh.token);
	printf("------------------\n");
	printf("[parsing]\n");
	print_process(g_sh.process);
	printf("------------------\n");
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
	g_sh.envp = envp;
	while (envp[++i])
	{
		tmp = split_env(envp[i]);
		make_env(env, tmp[0], tmp[1]);
	}
	g_sh.env = env;
}

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
