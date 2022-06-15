/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:30:02 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/15 16:26:03 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(t_data *a)
{	
	if (a->arg[1])
		if (chdir(a->arg[1]))
			printf("cd: no such file or directory: %s\n", a->arg[1]);
}