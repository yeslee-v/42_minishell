#include "../../includes/minishell.h"

char	*search_env_key(char *key, t_env *env) // use oldpwd
{
	while (env)
	{
		if (!(ft_strncmp(key, env->key, ft_strlen(env->key))))
			return (env->value);
		env = env->next;
	}
	return (NULL); // will make new list
}

// change value + return changed env list
// if need new list for export, unset(..), make new list >> jaekpark
t_env	*change_env_value(char *key, t_env *env)
{
	// value free + remalloc
	search_env_key(key, env);
	return (env);
}
