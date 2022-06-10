/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:49 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/10 17:50:06 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if ((a.line && !ft_strncmp(a.line, "exit", 5)) || !a.line)
		{
			//quit_shell(&a); //to do
			break ;
		}
		if (a.line && a.line[0] != '\0')
		{
			add_history(a.line);
			parsing(&a);
			//execution(&a);
		}
		free(a.prompt);
		a.prompt = NULL;
		free(a.line); // faut free la ligne a chaque fois sinon ca leaks de ouf
		a.line = NULL;
	}
	return (0);
}
