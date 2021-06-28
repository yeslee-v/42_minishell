/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:44:57 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/11 21:39:50 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write(int i, int fd)
{
	char c;

	if (i < 10)
	{
		i += '0';
		write(fd, &i, 1);
	}
	else
	{
		c = i % 10 + '0';
		i /= 10;
		ft_write(i, fd);
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n >= 0)
		ft_write(n, fd);
	else
	{
		n *= -1;
		write(fd, "-", 1);
		ft_write(n, fd);
	}
}
