/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:12:56 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:52:03 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;

	if (!src || !dst)
		return (0);
	srcsize = ft_strlen(src);
	if (dstsize == 0)
		return (srcsize);
	while (*src && --dstsize)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (srcsize);
}
