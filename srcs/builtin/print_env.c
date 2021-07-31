#include "../../includes/minishell.h"

t_env	*search_env_node(char *key, t_lst *env)
{
	t_env	*node;

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

char	*search_env_value(char *key, t_lst *env)
{
	t_env	*node;

	if (!key || !env)
		return (NULL);
	node = env->head;
	while (node)
	{
		if ((ft_strcmp(key, node->key)) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

t_env	*change_env_value(char *key, char *new_value, t_lst *env)
{
	char	*new;
	t_env	*target;

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

void	change_env_lst(char *bfore_key, char *after_key, t_lst *envl)
{
	char	*old_val;

	old_val = search_env_value(bfore_key, envl);
	change_env_value(after_key, old_val, envl);
}
