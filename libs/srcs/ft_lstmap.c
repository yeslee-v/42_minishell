/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:05:20 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:45:53 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_data;

	if (!lst || !f)
		return (NULL);
	new_node = NULL;
	while (lst)
	{
		new_data = ft_lstnew(f(lst->content));
		if (!new_data)
		{
			ft_lstclear(&new_data, del);
			break ;
		}
		ft_lstadd_back(&new_node, new_data);
		lst = lst->next;
	}
	return (new_node);
}
