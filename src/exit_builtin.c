#include "minishell.h"

void	exit_builtin(t_data *a)
{
	printf("exit\n");
	free(a->prompt);
	free(a->line);
	ft_double_free(a->arg);
	exit (1);
}
