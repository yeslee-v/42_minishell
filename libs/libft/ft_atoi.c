/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:33:38 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/10 21:14:02 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	sign;
	int cnt;
	int	result;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	cnt = 0;
	result = 0;
	while ((*str >= '0') && (*str <= '9'))
	{
		result = (result * 10) + (*str - '0');
		str++;
		cnt++;
	}
	if (cnt >= 19 && sign == 1)
		return (-1);
	else if (cnt >= 19 && sign == -1)
		return (0);
	return (sign * result);
}
