#include "../../../includes/minishell.h"

void	init_tool(t_tool *tool)
{
	tool->i = -1;
	tool->is_quote = 0;
	tool->st = -1;
	tool->ed = -1;
	tool->a_redir = 0;
	tool->redir = 0;
	tool->pipe = 0;
	tool->heredoc = 0;
}
