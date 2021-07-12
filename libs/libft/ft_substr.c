/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:03:24 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/18 16:50:22 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sub(char *c, char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < start)
		i++;
	j = 0;
	while (i < (start + len))
		c[j++] = (char)s[i++];
	c[j] = '\0';
	return (c);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		if (!(c = malloc(sizeof(char))))
			return (0);
		c[0] = '\0';
		return (c);
	}
	else
	{
		if (!(c = malloc(sizeof(char) * (len + 1))))
			return (0);
		ft_sub(c, s, start, len);
	}
	return (c);
}
