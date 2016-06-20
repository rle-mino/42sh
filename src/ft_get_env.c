/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:49:37 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/18 18:00:49 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_e		*ft_add_e(t_e *env, char *s)
{
	t_e			*temp;
	t_e			*temp2;

	temp = (t_e*)malloc(sizeof(t_e));
	temp->str = s ? ft_strdup(s) : NULL;
	temp->op = 0;
	temp->ret = 0;
	temp->status = 0;
	temp->err = NULL;
	temp->next = NULL;
	temp->export = NULL;
	if (!env)
		return (temp);
	temp2 = env;
	while (temp2->next)
		temp2 = temp2->next;
	temp2->next = temp;
	return (env);
}

t_e		*ft_get_env(int i)
{
	extern char	**environ;
	t_e			*env;
	char		*s;
	char		*s2;

	env = NULL;
	s = getcwd(NULL, 0);
	s2 = ft_strjoin("setenv PWD ", s);
	ft_strdel(&s);
	s = ft_strjoin(s2, " 1");
	ft_strdel(&s2);
	while (environ && environ[i])
	{
		env = ft_add_e(env, environ[i]);
		i++;
	}
	ft_strdel(&s);
	get_t_env(env);
	return (set_shlvl(env));
}

t_e		*ft_change_env(t_e *env, t_e *mod, char **t, int check)
{
	char		*s;
	char		*new;

	if (ft_strchr(t[1], '=') != NULL || ft_strchr(t[2], '=') != NULL)
		ft_putendl_fd("setenv: wrong arguments, arguments contain '='", 2);
	else if (t && mod && (!t[3] || check == 0 || ft_strequ(t[3], "1")))
	{
		s = ft_strjoin(t[1], "=");
		new = ft_strjoin(s, t[2]);
		ft_strdel(&mod->str);
		ft_strdel(&s);
		mod->str = new;
	}
	else if (ft_strequ(t[3], "0") == 0)
		ft_putendl_fd("setenv error: bad overwrite value", 2);
	return (env);
}

t_e		*ft_add_env(char **t, t_e *env, int check)
{
	char		*s;
	char		*s2;

	if (ft_strchr(t[1], '=') != NULL || ft_strchr(t[2], '=') != NULL)
		ft_putendl_fd("setenv: wrong arguments, arguments contain '='", 2);
	else if (!t[3]
			|| check == 0 || ft_strequ(t[3], "0") || ft_strequ(t[3], "1"))
	{
		s = ft_strjoin(t[1], "=");
		s2 = ft_strjoin(s, t[2]);
		env = ft_add_e(env, s2);
		ft_strdel(&s);
		ft_strdel(&s2);
	}
	else if (ft_strequ("0", t[3]) == 0 && ft_strequ("1", t[3]) == 0)
		ft_putendl_fd("setenv error: bad overwrite value", 2);
	return (env);
}

t_e		*ft_del_env(char *s, t_e *env)
{
	t_e			*temp;
	int			i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (s && s[i] && env->str && env->str[i] && s[i] == env->str[i])
		i++;
	if (!s[i] && env->str[i] == '=')
	{
		temp = env->next;
		ft_strdel(&(env->str));
		free(env);
		env = NULL;
		temp = ft_del_env(s, temp);
		return (temp);
	}
	else
	{
		env->next = ft_del_env(s, env->next);
		return (env);
	}
}
