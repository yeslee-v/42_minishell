/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 22:44:40 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:46:57 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	char	*dst_tmp;
	char	*src_tmp;

	dst_tmp = (char *)dst;
	src_tmp = (char *)src;
	if (!dst && !src)
		return (NULL);
	while (num--)
		*dst_tmp++ = *src_tmp++;
	return (dst);
}
