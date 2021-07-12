/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 21:49:00 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/18 15:47:41 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(int n)
{
	size_t	cnt;

	cnt = 1;
	while (n > 9)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static char		*ft_input(size_t i, size_t len, int n, char *c)
{
	while (i < len)
	{
		c[len - i - 1] = n % 10 + '0';
		n /= 10;
		i++;
	}
	return (c);
}

char			*ft_itoa(int n)
{
	size_t	i;
	size_t	len;
	char	*c;

	len = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		len += 1;
		n *= -1;
	}
	len += ft_size(n);
	i = 0;
	if (!(c = malloc(len + 1)))
		return (0);
	ft_input(i, len, n, c);
	if (len != ft_size(n))
		c[0] = '-';
	c[len] = '\0';
	return (c);
}
