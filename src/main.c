/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:17:56 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/07 00:02:46 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Je vais creer une function strNjoin 
//
char*	prompt(char **envp)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*user;
	int		i;
	
	i = ft_strlen(ft_strrchr(envp[21], '='));
	i--;
	temp = ft_strjoin(ft_substr(envp[21], i, i), "@");
	temp2 =	ft_strrchr(envp[7], '/');
	temp2++;
	temp3 = ft_strjoin(temp, temp2);
	user = ft_strjoin(temp3, ":~$ ");
	return (user);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*line;
	char	*user;
	struct sigaction sa;

	user = prompt(envp);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);	
	while (1)
	{
		line = calloc(50,sizeof(char));
		line = readline(user);
		if (line)
			add_history(line);
	}	
	free (line);
	free (user);
	return (0);
}
