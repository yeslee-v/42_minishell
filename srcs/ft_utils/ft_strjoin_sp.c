#include "../../includes/minishell.h"

static char	*ret_str(char *s1, char *s2)
{
	if (!(s1))
		return (ft_strdup(s2));
	else if (!(s2))
		return (s1);
	return (NULL);
}

char	*ft_strjoin_sp(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;

	i = -1;
	j = -1;
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (ret_str(s1, s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	while (s1[++i])
		newstr[i] = s1[i];
	newstr[i++] = ' ';
	while (s2[++j])
		newstr[i++] = s2[j];
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}
