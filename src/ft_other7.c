/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:17:11 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/17 15:57:42 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*** Set variables and verify if exists or not
*/

t_e				*ft_setexport(char **t, t_e *env, int i, int check)
{
	t_export	*temp;

	temp = env ? env->export : NULL;
	while (temp && t && t[i])
		i++;
	if (temp && !t[1])
		ft_export(t, env->export, 0);
	else if (temp && t[0] && ft_strequ(t[1], "-p") && !t[2])
		ft_export(t, env->export, 1);
	else if (temp && t && t[0] && t[1] && t[2])
	{
		while (temp)
		{
			if (ft_start_str(t[1], temp->export_env))
				return (ft_change_export(env, t, &temp, check));
			temp = temp->next;
		}
		return (ft_add_export_second(t, check, env));
	}
	else if (temp && (!back_strchr(t[1], '=') ||
	(t[2] && !back_strchr(t[2], '='))))
		env = ft_setexport2(env, &temp, t[1]);
	else if (temp)
		env = ft_setexport_err(env);
	return (env);
}

/*
*** SHLVL for export
*/

t_export		*set_shlvl_export(t_export *env)
{
	t_export	*temp;
	char		*tmp;
	int			i;

	temp = env;
	while (temp && !ft_start_str("SHLVL=", temp->export_env))
		temp = temp->next;
	if (!temp)
		return (ft_add_export(env, "SHLVL=1", true));
	i = ft_atoi(no_char(temp->export_env, '='));
	ft_strdel(&temp->export_env);
	tmp = ft_itoa(i + 1);
	temp->export_env = ft_strjoin("SHLVL=", tmp);
	ft_strdel(&tmp);
	return (env);
}

t_export		*get_t_export(t_export *e)
{
	static t_export	*ori_e = NULL;

	if (!ori_e)
		ori_e = e;
	return (ori_e);
}

/*
*** Just add env to export char * second
*/

t_export		*ft_add_export(t_export *env, char *s, bool b)
{
	t_export			*temp;
	t_export			*temp2;

	temp = (t_export *)ft_memalloc(sizeof(t_export));
	if (!temp)
		malloc_handling();
	temp->export_env = ft_strdup(s);
	temp->display = b;
	temp->status = 0;
	if (!env)
		return (temp);
	temp2 = env;
	while (temp2->next)
		temp2 = temp2->next;
	temp2->next = temp;
	return (env);
}

/*
*** Just add env to export char * first
*/

t_export		*ft_get_export(int i)
{
	extern char	**environ;
	t_export	*env;
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
		env = ft_add_export(env, environ[i], true);
		i++;
	}
	ft_strdel(&s);
	get_t_export(env);
	return (set_shlvl_export(env));
}
