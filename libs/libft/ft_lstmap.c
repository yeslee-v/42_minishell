/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:47:25 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/20 18:48:38 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	t_list	*temp;

	if (!lst || !f || !del)
		return (0);
	if (!(head = ft_lstnew((*f)(lst->content))))
		return (0);
	node = head;
	temp = lst->next;
	while (temp)
	{
		if (!(node->next = ft_lstnew((*f)(temp->content))))
		{
			ft_lstclear(&head, del);
			return (0);
		}
		node = node->next;
		temp = temp->next;
	}
	return (head);
}
