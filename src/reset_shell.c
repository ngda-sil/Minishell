
#include "minishell.h"

void	reset_shell(t_data *a, char **env)
{
	ft_bzero(a, sizeof(t_data));
	a->env = env_into_list(env);
	a->prompt = prompt(env); // rename get prompt?
}
