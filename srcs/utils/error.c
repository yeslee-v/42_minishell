/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:53:13 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/29 22:59:36 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	error_with_message(char *msg, int exit_status)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_sh.exit_status = exit_status;
}

void	exit_shell(int num)
{
	/*free(g_sh.cmd);*/
	/*free_lexer(g_sh.lexer);*/
	/*free_token(g_sh.token);*/
	/*free_process(g_sh.process);*/
	/*printf("exit\n");*/
	exit(num);
}
