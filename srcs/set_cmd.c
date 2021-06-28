/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 01:57:27 by yeslee            #+#    #+#             */
/*   Updated: 2021/06/25 22:35:09 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void		ft_cmd_intro(const char *cmd_1, char **path, t_cmd *st_cmd)
{
	int		i;
	char	**chunk;

	i = 0;
	if (!(ft_strlen(cmd_1)))
		ft_error_message("cmd_1 is not exists");
	chunk = ft_split(cmd_1, ' ');
	while (*path)
	{
		st_cmd->cmd[i] = ft_strjoin(*path, chunk[0]);
		i++;
		path++;
	}
	st_cmd->cmd[i] = NULL;
	st_cmd->av = (char *const *)chunk;
	st_cmd->envp = NULL;
}

void		ft_divid_path(const char *cmd_1, char **path, t_cmd *st_cmd)
{
	int		i;
	char	**str;
	char	*tmp[100];

	i = -1;
	str = NULL;
	while (*path)
	{
		if ((**path == 'P') && (*(*path + 1) == 'A') && (*(*path + 2) == 'T')
				&& (*(*path + 3) == 'H'))
		{
			str = ft_split(*path, ':');
			break ;
		}
		path++;
	}
	while (str[++i])
	{
		tmp[i] = ft_strjoin(str[i], "/");
		free(str[i]);
	}
	tmp[i] = NULL;
	free(str);
	ft_cmd_intro(cmd_1, tmp, st_cmd);
}
