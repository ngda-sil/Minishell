
#include "minishell.h"

void	quit_shell(t_data *a) //vrmt temporaire pour tester
{
	free (a->prompt);
	while (1);
	exit(1);
}

void	reset_shell(t_data *a, char **env)
{
	(void)env;
	ft_bzero(a, sizeof(t_data));
	//a->env = env_into_list(env);
	a->prompt = get_prompt();
}
