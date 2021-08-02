/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:43:42 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:54:22 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arr_size(unsigned long long n)
{
	int		count;

	count = 1;
	while (1)
	{
		if (n / 16 == 0)
			break ;
		n /= 16;
		count++;
	}
	return (count);
}

char	*ft_utoa(unsigned long long n, char *base_set)
{
	char	*dst;
	int		dstsize;

	dstsize = arr_size(n) + 1;
	dst = malloc(sizeof(char) * dstsize);
	dst[--dstsize] = '\0';
	while (1)
	{
		dst[--dstsize] = base_set[n % 16];
		n /= 16;
		if (n == 0)
			break ;
	}
	return (dst);
}
