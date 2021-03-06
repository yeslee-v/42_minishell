/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:41:40 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:46:44 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *ptr, int val, size_t num)
{
	unsigned char	*ptr_tmp;

	ptr_tmp = (unsigned char *)ptr;
	while (num--)
	{
		if (*ptr_tmp == (unsigned char)val)
			return (ptr_tmp);
		ptr_tmp++;
	}
	return (NULL);
}
