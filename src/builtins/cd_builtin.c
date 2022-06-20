/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:30:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/20 16:57:49 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(t_data *a, char **args)
{
	if (args[1])
	{
		if (chdir(args[1]))
			red_flag(ft_strjoin4("minishell: cd : ", args[1], ": ",strerror(errno)));
	}
	else
	{
		if (chdir(ft_getenv(a->env, "HOME")))
			red_flag("Problem with chdir going to $HOME\n");
	}
}

// echo $OLDPWD $PWD ; cd / ; echo $OLDPWD $PWD 
// a gerer exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'
