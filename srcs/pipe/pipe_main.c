int			main(int ac, char **av, char **path)
{
	pid_t	pid;
	t_pipe	pipe;
	int		status;

	if (ac != 5)
		print_error("The arguments are invalid");
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	else if (pid == 0)
		ft_pid_zero(av, path, &pipe);
	else
		print_error("fork error");
	return (0);
}
