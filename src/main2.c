
#include "minishell.h"

// Nouvelle version pour que ca marche avec le parsing

// faut pas allouer de memoire avant readline (comme gnl)

// je pense que c'est plus facile de reset le shell apres chaque commande
// pour avoir le bon prompt, le env up to date, ...

int	main(int argc, char **argv, char **env)
{
	t_data	a;

	(void)argc;
	(void)argv;
	// todo here signals and termios
	while (1)
	{
		reset_shell(&a, env);
		a.line = readline(a.prompt);
		if (a.line && !ft_strncmp(a.line, "exit", 5))
			quit_shell(&a); //to do
		if (a.line)
		{
			add_history(a.line);
			parsing(&a, line);
		}
		free(a.prompt);
		a.prompt = NULL;
	}
	return (0);
}
