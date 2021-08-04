#include "../../../includes/minishell.h"

void	print_token(t_lst *token)
{
	t_token	*temp;

	temp = token->head;
	while (temp)
	{
		printf(BLUE);
		printf("|[토큰] = %-18s| ", temp->token);
		printf("|타입 = %c| ", temp->type);
		printf("|순서 = %2d| ", temp->i);
		printf("|시작점 = %3d| |종료점 = %3d|\n", temp->st, temp->ed);
		printf(RESET);
		temp = temp->next;
	}
}

void	print_env(t_lst *env)
{
	t_env	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("==============================\n");
		printf("key = %s\nvalue = %s\n", tmp->key, tmp->value);
		printf("==============================\n");
		tmp = tmp->next;
	}
}
