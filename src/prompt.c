/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:34:44 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/06/21 02:55:47 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin4(char const *s1, char const *s2, char const *s3,
			char const *s4)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	if (!s1 || !s2 || !s3 || !s4)
		return (NULL);
	s = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)
			+ ft_strlen(s4) + 1, sizeof(char));
	if (!s)
		return (NULL);
	while (i < j)
		s[i++] = *s1++;
	j += ft_strlen(s2);
	while (i < j)
		s[i++] = *s2++;
	j += ft_strlen(s3);
	while (i < j)
		s[i++] = *s3++;
	j += ft_strlen(s4);
	while (i < j)
		s[i++] = *s4++;
	return (s);
}

char	*get_prompt(t_data *a)
{
	char	*tmp;
	char	*prompt;

	tmp = getcwd(NULL, 42);
	prompt = ft_strjoin4(ft_getenv(a->env, "USER"), "@", ft_strrchr(tmp, '/') + 1, ":$ ");
	free(tmp);
	return (prompt);
}
