/*
 *exeve test
 */

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
