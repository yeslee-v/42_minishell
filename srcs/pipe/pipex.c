/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:40:26 by yeslee            #+#    #+#             */
/*   Updated: 2021/07/16 15:03:55 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_pid_not_zero(char **av, char **path, t_exec *pipe)
{
	int		status;

	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	split_path(av[3], path, pipe);
	connect_out(av[4]);
	run_dup2(0, pipe);
	close_fd(3, pipe);
	run_execve(pipe);
}

static void	ft_pid_zero(char **av, char **path, t_exec *pipe)
{
	int		pid;

	pipe(pipe->fd);
	pid = fork();
	if (pid > 0)
		ft_pid_not_zero(av, path, pipe);
	else if (pid == 0)
	{
		split_path(av[2], path, pipe);
		connect_in(av[1]);
		run_dup2(1, pipe);
		close_fd(3, pipe);
		run_execve(pipe);
	}
	else
		print_error("fork error");
}
