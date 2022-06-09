
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

	init_signals(&a);
	while (1)
	{
		reset_shell(&a, env);
		a.line = readline(a.prompt);
		if ((a.line && (!ft_strncmp(a.line, "exit", 5))) || !a.line)
			quit_shell(&a); //to do
		if (a.line && ft_strncmp(a.line, "", 2)) // obliger de mettre ft_strncmp sinon les lignes vides sont dans l'historique
		{
			add_history(a.line);
			//parsing(&a, line);
		}
		free(a.prompt);
		a.prompt = NULL;
		free(a.line); // faut free la ligne a chaque fois sinon ca leaks de ouf
		a.line = NULL;
	}
	return (0);
}
