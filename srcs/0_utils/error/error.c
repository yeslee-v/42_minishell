/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:53:13 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 03:40:06 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	token_error(char *token, int exit_status)
{
	ft_putstr_fd(ERR_TOKEN, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\"\n", 2);
	g_sh.exit_status = exit_status;
}

int	redir_error(char *file, char *err_msg)
{
	ft_putstr_fd("BraveShell : ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	error_with_message(char *msg, int exit_status)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_sh.exit_status = exit_status;
}
