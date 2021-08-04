/*
 *exeve test
 */

int	check_echo_opt(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[0] == '-')
			i++;
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	check_echo_arg_lower(char **args)
{
	int i;
	int	opt;
	int size;
	int	ret;

	i = -1;
	opt = 0;
	ret = 0;
	if (!args)
		return (0);
	size = ft_double_strlen((const char **)args);
	if (size <= 2)
		return (0);
	while (args[++i])
	{
		while (opt == 0 && args[i])
		{
			if ((check_echo_opt(args[i])) != 1)
			{
				opt = -1;
				break ;
			}
		}
		ret += ft_strlen(args[i]) + 1;
	}
	ret--;
	return (ret);
}

int	check_uppercase(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			return (0);
	}
	return (1);
}

int	check_echo(t_process *node)
{
	int	ret;
	t_cmd *target;
	t_control *tmp;

	if (!node)
		return (0);
	tmp = node->con;
	target = node->cmd;
	if (!target)
		return (0);
	if (tmp || tmp->o_redir || tmp->o_redir->head)
		return (0);
	if (!target->cmd)
		return (0);
	if (check_uppercase(target->cmd))
		ret = check_echo_arg_lower(target->args);
	else
		ret = check_echo_arg_upper(target->args);
	return (ret);
}
	t_process *p;
	t_redirect *i;
	t_redirect *o;
	int j;
	char *cmd;
	int fd;
	int status;
	pid_t pid;

	j = 0;


	p = NULL;
		i = NULL;
		o = NULL;
		cmd = NULL;
		if (g_sh.cmd != NULL)
			p = g_sh.process->head;
		if (p && p->i_redir != NULL)
			i = p->i_redir->tail;
		if (p && p->o_redir != NULL)
			o = p->o_redir->tail;
		if (p && p->cmd)
			cmd = p->cmd->cmd;
		if (cmd != NULL && (ft_strcmp(cmd, "cat")) == 0)
		{
			pid = fork();
			if (pid > 0)
			{
				waitpid(0, &status, WUNTRACED);
				if (!(WIFEXITED(status)))
					exit(1);
			}
			if (pid == 0)
			{	
				if (i->type == 'H')
					fd = open(".hdoc/.hdoc_tmp", O_RDWR);
				else if (i->type == 'I')
					fd = open(i->arg, O_RDWR);
				dup2(fd, 0);
				if (o != NULL)
					dup2(o->fd, 1);
				if ((execve("/bin/cat", 0, 0)) == -1)
					printf("exec error\n");
				else
					exit(0);
			}



/* make buffer redir */
				else
				{
					while ((get_next_line(i_redir->fd, &line)) != 0)
					{
						line = ft_strjoin(line, "\n");
						input_redir = ft_double_strjoin(input_redir, line);
						free(line);
						line = NULL;
					}
					if (line)
						free(line);
					i_redir->buffer = input_redir;
					input_redir = NULL;
					/*if (i_redir != p->i_redir->tail)*/
						/*close(i_redir->fd);*/

/*t_token	*parse_token(t_token *tok, t_lst *syn, char **cmd_t, char **arg_t)*/
/*{*/
	/*char *target;*/

	/*target = NULL;*/
	/*if (tok->type == 'C')*/
		/**cmd_t = ft_strdup(tok->token);*/
	/*else if (tok->type == 'S')*/
		/**arg_t = ft_strjoin_sp(*arg_t, tok->token);*/
	/*else if (tok->type == 'T')*/
		/*target = ft_strdup(tok->token);*/
	/*else if ((ft_strchr("OIAH", tok->type)))*/
	/*{*/
		/*make_syntax(syn, *cmd_t, *arg_t);*/
		/**cmd_t = ft_strdup(tok->token);*/
		/*if (target != NULL)*/
			/*make_syntax(syn, *cmd_t, target);*/
		/**arg_t = NULL;*/
	/*}*/
	/*tok = tok->next;*/
	/*return (tok);*/
/*}*/


/*t_token	*parser(t_lst *process, t_token *tok)*/
/*{*/
	/*char	*cmd_t;*/
	/*char	*arg_t;*/
	/*t_lst	*syn;*/
	/*t_token	*tmp;*/

	/*cmd_t = NULL;*/
	/*arg_t = NULL;*/
	/*tmp = tok;*/
	/*syn = malloc(sizeof(t_lst));*/
	/*init_lst(syn);*/
	/*while (tmp)*/
	/*{*/
		/*if (tmp->i == -1)*/
		/*{*/
			/*tmp = tmp->next;*/
			/*break ;*/
		/*}*/
		/*else*/
			/*tmp = parse_token(tmp, syn, &cmd_t, &arg_t);*/
	/*}*/
	/*if (cmd_t)*/
		/*make_syntax(syn, cmd_t, arg_t);*/
	/*save_process(process, syn);*/
	/*return (tmp);*/
/*}*/



int	check_precede_fd(char *cmd, int i)
{
	int	start;

	start = 0;
	if (!cmd)
		return (0);
	while (i >= 0)
	{
		if ((ft_isnum(cmd[i])) == 1)
		{
			if (start == 0)
				start = 1;
			i--;
		}
		else
			break ;
int	check_echo_opt(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[0] == '-')
			i++;
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	check_echo_arg_lower(char **args)
{
	int i;
	int	opt;
	int size;
	int	ret;

	i = -1;
	opt = 0;
	ret = 0;
	if (!args)
		return (0);
	size = ft_double_strlen((const char **)args);
	if (size <= 2)
		return (0);
	while (args[++i])
	{
		while (opt == 0 && args[i])
		{
			if ((check_echo_opt(args[i])) != 1)
			{
				opt = -1;
				break ;
			}
		}
		ret += ft_strlen(args[i]) + 1;
	}
	ret--;
	return (ret);
}

int	check_uppercase(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			return (0);
	}
	return (1);
}

int	check_echo(t_process *node)
{
	int	ret;
	t_cmd *target;
	t_control *tmp;

	if (!node)
		return (0);
	tmp = node->con;
	target = node->cmd;
	if (!target)
		return (0);
	if (tmp || tmp->o_redir || tmp->o_redir->head)
		return (0);
	if (!target->cmd)
		return (0);
	if (check_uppercase(target->cmd))
		ret = check_echo_arg_lower(target->args);
	else
		ret = check_echo_arg_upper(target->args);
	return (ret);
}
	}
	if (start == 1 && i == -1)
		return (1);
	else if (start == 1 && i >= 0 && (ft_strchr(" <>", cmd[i])))
		return (1);
	return (0);
}

int	check_follow_fd(char *cmd, int i)
{
	int	size;
	int	start;

	size = 0;
	start = 0;
	if (!cmd || cmd[i] != '&')
		return (0);
	size = ft_strlen(cmd);
	if (i >= size)
		return (0);
	printf("ok\n");
	if (cmd[i] == '&')
		i++;
	while (i < size)
	{
		if ((ft_isnum(cmd[i])) == 1)
			start = 1;
		else
			break ;
		i++;
	}
	if (start == 1 && cmd[i] == '\0')
		return (1);
	else if (start == 1 && i < size && ft_strchr(" <>", cmd[i]))
		return (1);
	return (0);
}

void		mark_precede_fd(char *lex, char type, int i)
{
	if (!lex)
		return ;
	while (i >= 0)
	{
		if ((ft_isnum(g_sh.cmd[i])) == 1)
		{
			lex[i] = type;
			i--;
		}
		else
			break;
	}
}

void		mark_follow_fd(char *lex, char type, int *i)
{
	int size;

	size = ft_strlen(g_sh.cmd);
	(*i)++;
	if (*i >= size)
		return ;
	if (g_sh.cmd[*i] == '&')
		lex[*i] = 'f';
	printf("mark follow fd\n");
	if (!lex)
		return ;
	if (g_sh.cmd[*i] == '&')
		lex[(*i)++] = '&';
	while (*i < size)
	{
		if ((ft_isnum(g_sh.cmd[*i])) == 1)
			lex[*i] = type;
		else
			break ;
		(*i)++;
	}
}

int				analyze_append_redir(t_token *node)
{
	int	fd;
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	fd = -2;
	if (!node)
		return (-1);
	else if ((ft_isnum(node->token[0])) == 1)
		fd = ft_atoi(node->token);
	if (fd == -1)
		printf("BraveShell: file descriptor out of range: Bad file "
				"descriptor\n");
	else if (fd > 255)
		printf("BraveShell: %d: Bad file descriptor\n", fd);
	while ((ft_isnum(node->token[i])) == 1)
		i++;
	while (node->token[i])
	{
		cnt++;
		i++;
	}
	printf("mark cnt = %d\n", cnt);
	return (cnt);
}

int	check_fd_token(t_token *node)
{
	int	fd;

	fd = ft_atoi(node->token);
	if (fd == -1)
	{
		printf("BraveShell: file descriptor out of range: Bad file "
				"descriptor\n");
		return (-1);
	}
	else if (fd > 255)
	{
		printf("BraveShell: %d: Bad file descriptor\n", fd);
		return (-1);
	}
	return (1);
}


/*
 *int			check_last_token(void)
 *{
 *    char	*line;
 *    t_token	*node;
 *    t_lexer	*tmp;
 *    int		ret;
 *
 *    node = g_sh.token->tail;
 *    if (!node)
 *        return (-1);
 *    else if (node->token)
 *    {
 *        if (node->token[0] == '|')
 *        {
 *            while (TRUE)
 *            {
 *                signal(SIGINT, SIG_DFL);
 *                signal(SIGQUIT, SIG_IGN);
 *                line = readline("> ");
 *                if (ft_strlen(line) > 0)
 *                {
 *                    g_sh.cmd = ft_strjoin_sp(g_sh.cmd, line);
 *                    tmp = lexer(g_sh.cmd);
 *                    free_lexer(g_sh.lexer);
 *                    printf("cmd = %s, tmp lex = %s\n",g_sh.cmd, tmp->lex);
 *                    g_sh.lexer = tmp;
 *                    free_token(g_sh.token);
 *                    g_sh.token = malloc(sizeof(t_lst));
 *                    init_lst(g_sh.token);
 *                    ret = tokenizer(tmp->lex);
 *                    free(line);
 *                    break ;
 *                }
 *                rl_redisplay();
 *                free(line);
 *            }
 *        }
 *    }
 *    return (analyze_syntax(g_sh.token));
 *}
 */

/*void	get_target_pos(char *str, char *target, int *st, int *ed)*/
/*{*/
	/*int	i;*/

	/*i = *st;*/
	/*if (!str || !target)*/
		/*return ;*/
	/*while (str[i])*/
	/*{*/
		/*if (str[i] == target[0])*/
		/*{*/
			/*if (ft_strncmp(&str[i], target, ft_strlen(target)) == 0)*/
			/*{*/
				/**st = i;*/
				/**ed = i + (ft_strlen(target) - 1);*/
				/*return ;*/
			/*}*/
		/*}*/
		/*i++;*/
	/*}*/
/*}*/
int	check_env_in_cmd(char *str)
{
	char	*ret;
	int		st;
	int		i;
	int		j;

	ret = NULL;
	st = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			j = i;
			st = i;
			while (str[++j])
				if ((ft_isalpha(str[j])) == 0)
					break ;
			if ((st == j || st == j - 1) && str[j] != '\0')
				return (0);
			else
				return (1);
		}
	}
	return (0);
}


int	get_char_cnt(char *lex)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	if (!lex)
		return (-1);
	while (lex[++i])
	{
		if (ft_strchr("dqc", lex[i]))
			cnt++;
	}
	return (cnt);
}
char	*token_dup_only_char(char *lex, t_token *node)
{
	char	*ret;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	if (!lex || !node)
		return (NULL);
	size = get_char_cnt(lex);
	ret = malloc(sizeof(char) * (size + 1));
	while (lex[++i])
	{
		if (ft_strchr("dqc", lex[i]))
		{
			ret[j] = node->token[i];
			j++;
		}
	}
	ret[size] = '\0';
	return (ret);
}

void	remove_quote(t_lst *token)
{
	t_token	*node;
	t_lexer	*tmp;
	char	*buf;
	int		i;

	i = -1;
	buf = NULL;
	if (!token)
		return ;
	node = token->head;
	while (node)
	{
		tmp = lexer(node->token);
		if ((check_quote_exist(tmp->lex)) == 1)
		{
			buf = token_dup_only_char(tmp->lex, node);
			free(node->token);
			node->token = ft_strdup(buf);
			free(buf);
		}
		free_lexer(tmp);
		tmp = NULL;
		node = node->next;
	}
}


	if ((node->token[0] == 34 || node->token[0] == 39) && (ft_strlen(node->token)) == 2)
		{
			tmp = ft_strdup("");
			free(node->token);
			node->token = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
		}
		else if ((check_quote_exist(g_sh.lexer->lex, node)) == 1)
		{
			tmp = strdup_only_char(g_sh.lexer->lex, node);
			free(node->token);
			node->token = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
