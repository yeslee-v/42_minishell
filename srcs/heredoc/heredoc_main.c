int			main(int ac, char **av, char **path)
{
	int		status;
	pid_t	pid;
	t_all	all;

	if (ac != 4)
		printf("invalid ac\n");
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	else if (pid == 0)
		set_first_fork(av, path, &all);
	else
		write(2, "fork error\n", 11);
	return (0);
}
