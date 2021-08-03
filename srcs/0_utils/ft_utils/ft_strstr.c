#include "../../../includes/minishell.h"

char	*ft_strstr(char *str, char *src)
{
	int	i;

	i = -1;
	if (!str || !src)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == src[0])
		{
			if ((ft_strncmp(&str[i], src, ft_strlen(src))) == 0)
				return (&str[i]);
		}
	}
	return (NULL);
}
