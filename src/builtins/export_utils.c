/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:16:09 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/20 16:22:54 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_new_env(t_env **lst, char *arg)
{
	int	name_len;

	if (ft_strchr(arg, '+'))
	{
		name_len = ft_strchr(arg, '+') - arg;
		lstadd_back_env(&(*lst), lstnew_env(arg, name_len, 1));
	}
	else
	{
		if (ft_strchr(arg, '='))
			name_len = ft_strchr(arg, '=') - arg;
		else
			name_len = ft_strlen(arg);
		lstadd_back_env(&(*lst), lstnew_env(arg, name_len, 0));
	}
}


int	is_in_new_env(t_env *lst, char *arg)
{
	int	name_len;

	if (!lst)
		return (1);
	while (lst)
	{
		name_len = ft_strlen(lst->name);
		if (!ft_strncmp(lst->name, arg, name_len) && (!arg[name_len] || (arg[name_len] == '=' || arg[name_len] == '+')))
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	check_arg_name(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]) || arg[i] == '=')
		return (1);
	i = -1;
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=')
		{
			if ((arg[i] == '+' && arg[i + 1] == '='))
				return(0);
			return (1);
		}
		if (arg[i] == '=')
			return (0);
	}
	return (0);
}

void	replace_in_new_env(t_env *lst, char *arg)
{
	int		name_len;
	char	*tmp;

	while (lst)
	{
		name_len = ft_strlen(lst->name);
		if (!ft_strncmp(lst->name, arg, name_len) && (arg[name_len] == '='))
		{
			tmp = lst->value;
			lst->value = ft_substr(arg, name_len + 1, ft_strlen(arg));
			free(tmp);
			break;
		}
		if (!ft_strncmp(lst->name, arg, name_len) && (arg[name_len] == '+'))
		{
			if (lst->value)
			{
				tmp = lst->value;
				lst->value = ft_strjoin(tmp, &arg[name_len + 2]);
				free(tmp);
			}
			else
			{
				lst->value = ft_strdup(&arg[name_len + 2]);
			}
			break;
		}

		lst = lst->next;
	}
}
