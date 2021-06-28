/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 03:33:30 by yeslee            #+#    #+#             */
/*   Updated: 2021/06/25 17:31:25 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_connect_i(char *file, int dest_fd)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error_message("The file is not open");
	if (dup2(fd, dest_fd) == -1)
		ft_error_message("dup2 error");
	if (close(fd) == -1)
		ft_error_message("close error");
}

void	ft_connect_o(char *file, int dest_fd)
{
	int	fd;

	if ((fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644)) < 0)
		ft_error_message("The file is not open");
	if (dup2(fd, dest_fd) == -1)
		ft_error_message("dup2 error");
	if (close(fd) == -1)
		ft_error_message("close error");
}

void	ft_dup2(int fd, t_cmd *cmd)
{
	if (fd == 1)
	{
		if (dup2(cmd->fd[1], fd) == -1)
			ft_error_message("dup2 error");
	}
	else if (fd == 0)
	{
		if (dup2(cmd->fd[0], fd) == -1)
			ft_error_message("dup2 error");
	}
}

void	ft_close(int flag, t_cmd *cmd)
{
	if (flag == 1)
	{
		if (close(cmd->fd[0]) == -1)
			ft_error_message("close(fd[0]) error");
	}
	else if (flag == 2)
	{
		if (close(cmd->fd[1]) == -1)
			ft_error_message("close(fd[1]) error");
	}
	else if (flag == 3)
	{
		if (close(cmd->fd[0]) == -1)
			ft_error_message("close(fd[0]) error");
		if (close(cmd->fd[1]) == -1)
			ft_error_message("close(fd[1]) error");
	}
}
