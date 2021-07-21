#include "../../includes/minishell.h"

int		get_redir_fd(char *cmd)
{
	int i;
	int fd;

	i = -1;
	fd = 0;
	if (!cmd || (ft_strlen(cmd)) >= 6)
		return (-1);
	while (cmd[++i])
	{
		printf("%c\n", cmd[i]);
		if ((ft_isnum(cmd[i])) == 1)
			fd = (fd * 10) + (cmd[i] - '0');
		else
			break ;

	}
	if (fd > 255 || fd < 0)
		return (-1);
	return (fd);
}

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	delete_env_node(char *key, t_lst *env)
{
	t_env *prev;
	t_env *node;
	t_env *next;

	if (!env)
		return ;
	prev = NULL;
	next = NULL;
	node = search_env_node(key, env);
	if (!node)
		return ;
	else if (node == env->head && node == env->tail)
	{
		free_env_node(node);
		node = NULL;
		env->head = NULL;
		env->tail = NULL;
	}
	else if (node == env->head && node != env->tail)
	{
		env->head = node->next;
		node->next->prev = NULL;
		free_env_node(node);
	}
	else if (node != env->head && node == env->tail)
	{
		env->tail = node->prev;
		node->prev->next = NULL;
		free_env_node(node);
	}
	else
	{
		prev = node->prev;
		next = node->next;
		prev->next = next;
		next->prev = prev;
		free_env_node(node);
	}
}
