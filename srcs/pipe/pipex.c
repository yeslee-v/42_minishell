/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:40:26 by yeslee            #+#    #+#             */
/*   Updated: 2021/06/25 17:13:27 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	ft_pid_not_zero(char **av, char **path, t_cmd *cmd)
{
	int		status;

	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	ft_divid_path(av[3], path, cmd);
	ft_connect_o(av[4], 1);
	ft_dup2(0, cmd);
	ft_close(3, cmd);
	ft_execve(cmd);
}

static void	ft_pid_zero(char **av, char **path, t_cmd *cmd)
{
	int		pid;

	pipe(cmd->fd);
	pid = fork();
	if (pid > 0)
		ft_pid_not_zero(av, path, cmd);
	else if (pid == 0)
	{
		ft_divid_path(av[2], path, cmd);
		ft_connect_i(av[1], 0);
		ft_dup2(1, cmd);
		ft_close(3, cmd);
		ft_execve(cmd);
	}
	else
		ft_error_message("fork error");
}

int			main(int ac, char **av, char **path)
{
	pid_t	pid;
	t_cmd	cmd;
	int		status;

	if (ac != 5)
		ft_error_message("The arguments are invalid");
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	else if (pid == 0)
		ft_pid_zero(av, path, &cmd);
	else
		ft_error_message("fork error");
	return (0);
}
