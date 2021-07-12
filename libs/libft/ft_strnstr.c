/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:33:15 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/10 17:28:50 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	else
	{
		while (big[i] && i < len)
		{
			j = 0;
			while (big[i + j] && big[i + j] == little[j] && (i + j) < len)
			{
				j++;
				if (!little[j])
					return ((char *)&big[i]);
			}
			i++;
		}
	}
	return (0);
}
