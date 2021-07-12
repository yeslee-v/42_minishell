/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:40:27 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/09 20:39:06 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp;
	const unsigned char	*s;

	temp = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!temp && !s)
		return (0);
	else if (dest <= src)
	{
		while (n--)
			*temp++ = *s++;
	}
	else
	{
		temp += n;
		s += n;
		while (n--)
			*--temp = *--s;
	}
	return (dest);
}
