/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:49 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/21 20:22:41 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	main2(int ac, char **av, char **env)
{
	t_data	a;

	(void)av;
	ft_bzero(&a, sizeof(t_data));
	if (ac == 1)
	{
		init_signals(&a);
		while (1)
		{
			reset_shell(&a, env);
			a.line = readline(a.prompt);
			if (!a.line)
				break ;
			if (a.line && a.line[0] != '\0')
			{	
				add_history(a.line);
				if (parsing(&a))
					continue ;
				execution(&a, a.cmd, env);
			}
		}
		rl_clear_history();
		free_all(&a);
	}
	return (0);
}*/

int	main2(char *str, char **env)
{
	t_data	a;
	int		i;

	ft_bzero(&a, sizeof(t_data));
	init_signals(&a);
	i = 1;
	while (i)
	{
		reset_shell(&a, env);
		if (str)
		{
			a.line = str;
			i = 0;
		}
		else
			a.line = readline(a.prompt);
		if (!a.line)
			break ;
		if (a.line && a.line[0] != '\0')
		{	
			add_history(a.line);
			if (parsing(&a))
				continue ;
			execution(&a, a.cmd, env);
		}
		rl_clear_history();
		//free_all(&a);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	exit_status;

	if (argc == 1)
		main2(NULL, env);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		exit_status = main2(argv[2], env);
		exit(exit_status);
	}
}
