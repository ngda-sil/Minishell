/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:17:56 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/07 17:41:34 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*line;
	char	*user;
	struct sigaction sa;
	struct termios ter;

	ter.c_lflag &= ~(ECHOE | ICANON);
	user = prompt(envp);
	sa.sa_sigaction = handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);	
	while (1)
	{
		line = calloc(50,sizeof(char));
		line = readline(user);
		if (line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
			break;
	}	
	free (line);
	free (user);
	return (0);
}
