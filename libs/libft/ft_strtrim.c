/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeslee <yeslee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:58:33 by yeslee            #+#    #+#             */
/*   Updated: 2020/10/18 21:10:06 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_f_size(char const *s1, char const *set)
{
	size_t	j;
	size_t	cnt;

	cnt = 0;
	while (*s1)
	{
		j = 0;
		while (set[j])
		{
			if (*s1 == set[j])
			{
				cnt++;
				break ;
			}
			j++;
		}
		s1++;
		if (!set[j])
			break ;
	}
	return (cnt);
}

static size_t	ft_b_size(char const *s1, char const *set)
{
	size_t	j;
	size_t	cnt;
	size_t	size;

	cnt = 0;
	size = ft_strlen(s1);
	while (size > 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[size - 1] == set[j])
			{
				cnt++;
				break ;
			}
			j++;
		}
		size--;
		if (!set[j])
			break ;
	}
	return (cnt);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	cnt;
	char	*s2;

	if (!s1 || !set)
		return (0);
	cnt = ft_strlen(s1) - (ft_f_size(s1, set) + ft_b_size(s1, set));
	if (ft_strlen(s1) == ft_f_size(s1, set))
		return (ft_strdup(""));
	if (!(s2 = malloc(cnt + 1)))
		return (0);
	i = 0;
	while (i < cnt)
	{
		s2[i] = s1[i + ft_f_size(s1, set)];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
