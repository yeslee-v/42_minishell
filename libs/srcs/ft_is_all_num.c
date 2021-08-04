/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_all_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 01:43:14 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 04:41:01 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_allnum(char **str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != NULL)
	{
		if ((ft_strnum(str[i])) == -1)
			return (-1);
		i++;
	}
	return (1);
}
