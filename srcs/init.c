/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:15:00 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/02 20:06:02 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_flag(t_flag *flag)
{
	flag->st = 0;
	flag->ed = 0;
	flag->quote = 0;
	flag->d_quote = 0;
}

void	init_lst(t_lst *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
