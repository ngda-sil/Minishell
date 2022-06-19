/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:46:36 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/20 00:38:43 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	swap_env(t_env **p1, t_env **p2)
{
	t_env	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	sort_env_list(t_env *lst)
{
	int		i;
	int		j;
	t_env	**p;
	t_env	*temp_l;

	j = -1;
	i = env_lstsize(lst);
	temp_l = lst;
	p = ft_calloc(i, sizeof(t_env *) + 1);
	while (++j < i)
	{
		p[j] = temp_l;
		temp_l = temp_l->next;
	}
	while (--i > 0)
	{
		j = -1;
		while (++j < i - 1)
			if (ft_strcmp(p[j]->name, p[j + 1]->name) > 0)
				swap_env(&p[j], &p[j + 1]);
	}
	j = -1;
	while (p[++j])
	{
		if (p[j]->value)
			printf("declare -x %s=\"%s\"\n", p[j]->name, p[j]->value);
		else
			printf("declare -x %s\n", p[j]->name);
	}
	free(p);
}

void	add_to_new_env(t_env **lst, char *arg)
{
	int	name_len;
	
	if (ft_strchr(arg, '='))
		name_len = ft_strchr(arg, '=') - arg;
	if (ft_strchr(arg, '+'))
		name_len = ft_strchr(arg, '+') - arg;
	else
		name_len = ft_strlen(arg);
	lstadd_back_env(&(*lst), lstnew_env(arg, name_len));
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
		if (!ft_isalnum(arg[i]) && arg[i] != '"' && arg[i] != '=')
		{
			if (arg[i] == '+' && arg[i + 1] == '=')
				continue;
			return (1);
		}
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
			tmp = lst->value;
			lst->value = ft_strjoin(tmp, &arg[name_len + 2]);
			free(tmp);
			break;
		}

		lst = lst->next;
	}
}

void	export_builtin(t_data *a, char **args)
{
	int		i;
	
	i = 1;
	if (!args[i])
		sort_env_list(a->env);
	else
	{
		while (args[i])
		{
			if (check_arg_name(args[i]))
			{
				red_flag("minishell : not a valid identifier");
				break;
			}
			if (!is_in_new_env(a->new_env, args[i]))
				replace_in_new_env(a->new_env, args[i]);
			else
				add_to_new_env(&a->new_env, args[i]);
			i++;
		}
		print_env_list((a->new_env));
	}
}
