/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:49 by amuhleth          #+#    #+#             */
/*   Updated: 2022/07/27 20:23:44 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	a;

	(void)av;
	ft_bzero(&a, sizeof(t_data));
	if (ac == 1)
	{
		while (1)
		{
			reset_shell(&a, env);
			a.line = readline(a.prompt);
			if (!a.line || !ft_strncmp(a.line, "exit", 5))
				break ;
			if (a.line && a.line[0] != '\0')
			{	
				add_history(a.line);
				if (parsing(&a))
					continue ;
				execution(&a, a.cmd, env);
			}
		}
		printf("exit\n");
		rl_clear_history();
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &a.origin);
		free_all(&a);
	}
	return (0);
}
/*
int	main2(char *str, char **env)
{
	t_data	a;
	int		i;

	ft_bzero(&a, sizeof(t_data));
	i = 1;
	while (i)
	{
		reset_shell(&a, env);
		if (str)
		{
			a.line = ft_strdup(str);
			i = 0;
		}
		else
		{
			ft_putstr_fd(a.prompt, STDERR_FILENO);
			a.line = readline("");
		}
		if (!a.line || !ft_strncmp(a.line, "exit", 5))
			break ;
		if (a.line && a.line[0] != '\0')
		{	
			add_history(a.line);
			if (parsing(&a))
				continue ;
			execution(&a, a.cmd, env);
		}
	}
	//printf("exit\n");
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &a.origin);
	free_all(&a);
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
}*/
