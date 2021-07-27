/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:53:13 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/26 21:30:24 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	exit_shell(int num)
{
	free(g_sh.cmd);
	free_lexer(g_sh.lexer);
	free_token(g_sh.token);
	free_process(g_sh.process);
	printf("exit\n");
	exit(num);
}
