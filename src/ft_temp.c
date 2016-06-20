/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_temp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 12:38:43 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/08 17:21:09 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		check_empty(char *s, int i, int j)
{
	if (j == 0)
		return (0);
	while (j > 0)
	{
		if (i - j != 0 && s[i + (i - j)] != ' ' && s[i + (i - j)] != '\t')
			return (0);
		j--;
	}
	return (1);
}

char	*ft_strarg(char *arg)
{
	char	*s;
	char	*s2;
	char	*s3;

	s = ft_str_trunc(arg, '=');
	s2 = ft_strjoin("setenv ", s);
	ft_strdel(&s);
	s = ft_strdup(no_char(arg, '='));
	s3 = ft_strlink(s2, s, ' ');
	ft_strdel(&s);
	ft_strdel(&s2);
	s2 = ft_strjoin(s3, " 1");
	ft_strdel(&s3);
	return (s2);
}

t_e		*ft_gettmp(t_e *env, char **t)
{
	t_e		*ret;
	t_e		*tmp;
	int		i;
	char	*s;

	tmp = env;
	ret = NULL;
	i = 1;
	while (tmp)
	{
		ret = ft_add_e(ret, tmp->str);
		tmp = tmp->next;
	}
	while (t[i] && back_strchr(t[i], '=') != NULL)
	{
		s = ft_strarg(t[i]);
		ret = call_builtins(s, ret, 1);
		ft_strdel(&s);
		i++;
	}
	return (ret);
}

char	**switch_env(t_e *env)
{
	char	**ret;
	t_e		*tmp;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ret = (char**)malloc(sizeof(char*) * (i + 1));
	ret[i] = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

void	ft_deltmp(t_e *env)
{
	t_e		*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		ft_strdel(&tmp->str);
		free(tmp);
	}
}
