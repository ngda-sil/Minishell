/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_into_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:08:01 by amuhleth          #+#    #+#             */
/*   Updated: 2022/06/19 20:06:05 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = lstlast_env(*lst);
		last->next = new;
	}
}

t_env	*lstnew_env(char *line, int name_len, int sep)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->name = ft_substr(line, 0, name_len);
	if (ft_strlen(line) == (size_t)name_len)
		new->value = NULL;
	else
		new->value = ft_strdup(line + name_len + 1 + sep);
	new->next = NULL;
	return (new);
}

t_env	*env_into_list(char **env)
{
	t_env	*lst;
	int		i;
	int		name_len;

	lst = NULL;
	i = 0;
	while (env[i])
	{
		name_len = ft_strchr(env[i], '=') - env[i];
		lstadd_back_env(&lst, lstnew_env(env[i], name_len, 0));
		i++;
	}
	return (lst);
}

char	*ft_getenv(t_env *lst, char *name)
{
	while (lst)
	{
		if (!ft_strncmp(name, lst->name, ft_strlen(lst->name) + 1))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	print_env_list(t_env *lst)
{
	while (lst)
	{
		printf("Name:%s, value:(%s)\n", lst->name, lst->value);
		lst = lst->next;
	}
}
