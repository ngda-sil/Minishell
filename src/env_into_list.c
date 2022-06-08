
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
		last = ft_lstlast(*alst);
		last->next = new;
	}
}

t_env	*lstnew_env(char *line)
{
	t_env	*new;
	int		name_len;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	name_len = ft_strchr(env[i], '=') - env[i];
	new->name = ft_substr(line, 0, name_len);
	new->value = ft_strdup(line + name_len + 1);
	new->next = NULL;
	return (new);
}

t_env	*env_into_list(char **env)
{
	t_env	*lst;
	int		i;

	i = 0;
	while (env[i])
	{
		name_len = ft_strchr(env[i], '=') - env[i];
		lstadd_back_env(&lst, lstnew_env(env[i]);
		i++;
	}
}
