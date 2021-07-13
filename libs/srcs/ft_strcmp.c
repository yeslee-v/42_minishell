/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:47:35 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/13 20:39:47 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-2);
	while (i < ft_strlen(s1))
	{
		if (s1[i] != s2[i])
			return (-3);
		i++;
	}
	return (0);
}
