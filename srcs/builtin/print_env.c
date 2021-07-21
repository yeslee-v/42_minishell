#include "../../includes/minishell.h"

t_env	*search_env_node(char *key, t_lst *env)
{
	t_env *node;
	
	if (!key || !env)
		return (NULL);
	node = env->head;
	while (node)
	{
		if ((ft_strcmp(key, node->key)) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*search_env_value(char *key, t_lst *env) // use oldpwd
{
	t_env *node;

	if (!key || !env)
		return (NULL);
	node = env->head;
	while (node)
	{
		if ((ft_strcmp(key, node->key)) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL); // will make new list
}

// change value + return changed env list
// if need new list for export, unset(..), make new list >> jaekpark
t_env	*change_env_value(char *key, char *new_value, t_lst *env)
{
	char	*new;
	t_env *target;
	
	if (!key || !env)
		return (NULL);
	target = search_env_node(key, env);
	if (!target)
		return (NULL);
	if (target->value)
		free(target->value);
	new = ft_strdup(new_value);
	target->value = new;
	return (target);
}
