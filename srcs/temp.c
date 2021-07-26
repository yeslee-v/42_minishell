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

