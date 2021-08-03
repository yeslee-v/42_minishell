#include "../../../includes/minishell.h"

static void	delete_first_node(t_lst *env, t_env *node)
{
	env->head = node->next;
	node->next->prev = NULL;
	free_env_node(node);
}

static void	delete_last_node(t_lst *env, t_env *node)
{
	env->tail = node->prev;
	node->prev->next = NULL;
	free_env_node(node);
}

static void	delete_inter_node(t_env *node)
{
	t_env	*prev;
	t_env	*next;

	prev = node->prev;
	next = node->next;
	prev->next = next;
	next->prev = prev;
	free_env_node(node);
}

void	delete_env_node(char *key, t_lst *env)
{
	t_env	*node;

	if (!env)
		return ;
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
		delete_first_node(env, node);
	else if (node != env->head && node == env->tail)
		delete_last_node(env, node);
	else
		delete_inter_node(node);
}
