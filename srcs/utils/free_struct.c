#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	free_conf(t_conf *conf)
{
	if (!conf)
		return ;
	if (conf->cmd)
		free(conf->cmd);
	if (conf->lexer)
		free_lexer(conf->lexer);
	if (conf->token)
		free_token(conf->token);
	if (conf->process)
		free_process(conf->process);
}

void	free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	else if (lexer->lex != NULL)
		free(lexer->lex);
	free(lexer);
}

void	free_cmd(t_cmd *node)
{
	if (!node)
		return ;
	if (node->cmd)
		free(node->cmd);
	if (node->arg)
		free(node->arg);
	if (node->args)
		ft_free_double((void **)node->args);
	if (node->bin)
		free(node->bin);
	if (node->input_redir)
		free(node->input_redir);
	if (node->output_redir)
		free(node->output_redir);
	free(node);
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
