/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:04:41 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:44:48 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*last_add;

	if (!lst || !new_lst)
		return ;
	if (!*lst)
	{
		*lst = new_lst;
		return ;
	}
	last_add = ft_lstlast(*lst);
	last_add->next = new_lst;
}
