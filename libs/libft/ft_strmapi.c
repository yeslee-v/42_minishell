/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:20:37 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/14 21:11:10 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*c;
	unsigned int	i;
	unsigned int	size;

	if (!s || !(*f))
		return (0);
	i = 0;
	size = ft_strlen(s);
	c = malloc(sizeof(char) * (size + 1));
	if (!c)
		return (0);
	while (s[i])
	{
		c[i] = (*f)(i, s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}
