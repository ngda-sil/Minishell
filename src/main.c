/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:17:56 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/08 23:54:12 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char	*line;
	char	*p;

	p = prompt();
	init_signals();
	while (1)
	{
		line = calloc(50, sizeof(char));
		line = readline(p);
		if (ft_strncmp(line, "", 1))
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
			break ;
		free (line);
	}
	rl_clear_history();
	free (p);
	free (line);
	return (0);
}
