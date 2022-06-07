/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:17:56 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/07 16:59:21 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
// Je vais creer une function strNjoin 

void	handler(int	sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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
