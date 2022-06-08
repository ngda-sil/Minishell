/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:17:56 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/08 21:53:20 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*line;
	char	*user;

	user = prompt(envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = calloc(50, sizeof(char));
		line = readline(user);
		if (line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
			break ;
	}
	rl_clear_history();
	free (line);
	free (user);
	return (0);
}
