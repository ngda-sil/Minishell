#include "../minishell.h"

void	exit_builtin(t_data *a)
{
	printf("exit\n");
	free(a->prompt);
	free(a->line);
	exit (1);
}
