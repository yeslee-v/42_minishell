/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:43:42 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:58:25 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	arr_size(int n)
{
	int		count;

	count = 1;
	while (1)
	{
		if (n / 10 == 0)
			break ;
		n /= 10;
		count++;
	}
	return (count);
}

void	set_dstsize(int *dstsize, int n)
{
	if (n < 0)
		*dstsize = arr_size(n) + 2;
	else
		*dstsize = arr_size(n) + 1;
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		dstsize;

	dstsize = 0;
	set_dstsize(&dstsize, n);
	dst = malloc(sizeof(char) * dstsize);
	dst[--dstsize] = '\0';
	if (n < 0)
	{
		dst[0] = '-';
		if (n == -2147483648)
		{
			dst[1] = '2';
			n = -147483648;
		}
		n *= -1;
	}
	while (1)
	{
		dst[--dstsize] = n % 10 + '0';
		n /= 10;
		if (n == 0)
			break ;
	}
	return (dst);
}
