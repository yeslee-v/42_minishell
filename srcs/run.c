/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:06:26 by yeslee            #+#    #+#             */
/*   Updated: 2021/06/25 17:14:52 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_execve(t_cmd *st_cmd)
{
	int	i;

	i = ft_double_len(st_cmd->cmd);
	while (--i >= 0)
		execve(st_cmd->cmd[i], st_cmd->av, st_cmd->envp);
	ft_error_message("execve error");
}
