#include "../../includes/minishell.h"

char	**ft_double_strjoin(char **dst, char *src)
{
	char	**ret;
	int size;
	int i;

	i = 0;
	size = 0;
	ret = NULL;
	if (!dst)
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = ft_strdup(src);
		ret[1] = NULL;
		return (ret);
	}
	else if (dst)
	{
		size = ft_double_strlen((const char **)dst);
		ret =  malloc(sizeof(char *) * (size + 2));
		while (dst[i] != NULL)
		{
			ret[i] = ft_strdup(dst[i]);
			i++;
		}
		ret[i] = ft_strdup(src);
		ret[i + 1] = NULL;
		ft_free_double((void **)dst);
		dst = NULL;
		return (ret);
	}
	return (ret);
}
