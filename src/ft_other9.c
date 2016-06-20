/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:53:03 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/12 11:48:36 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*** Display Export Env
*/

void			ft_export(char **t, t_export *env, int status)
{
	t_export		*temp;

	(void)&t;
	temp = env;
	if (status == 0)
	{
		while (temp)
		{
			if (temp->display)
				ft_putendl(temp->export_env);
			temp = temp->next;
		}
	}
	else if (status == 1)
	{
		while (temp)
		{
			if (temp->display)
			{
				ft_putstr("typeset -x ");
				ft_putendl(temp->export_env);
			}
			temp = temp->next;
		}
	}
}

t_export		*ft_del_export(char *s, t_export *env)
{
	t_export	*temp;
	int			i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (s && s[i] && env->export_env && env->export_env[i]
		&& s[i] == env->export_env[i])
		i++;
	if (!s[i] && env->export_env[i] == '=')
	{
		temp = env->next;
		free(env->export_env);
		free(env);
		temp = ft_del_export(s, temp);
		return (temp);
	}
	else
	{
		env->next = ft_del_export(s, env->next);
		return (env);
	}
}

void			ft_unset_second(char **t, t_export *temp)
{
	while (temp)
	{
		if (ft_start_str(t[1], temp->export_env)
				&& temp->export_env[ft_strlen(t[1])] == '=')
			break ;
		temp = temp->next;
	}
}

void			ft_unset_first(char **t, t_export *env)
{
	if (!t[1])
		ft_putendl_fd("unset error: no arguments to unset", 2);
	if (t[1] && t[2])
		ft_putendl_fd("unset error: too many arguments", 2);
	if (env)
		env->status = 1;
}

/*
*** Unset variables.
*/

t_export		*ft_unset(char **t, t_export *env, int i, t_e *e)
{
	t_export		*temp;

	temp = env;
	if (t && t[0] && ((t[1] && t[2]) || !t[1]))
		ft_unset_first(t, env);
	else
	{
		ft_unset_second(t, temp);
		if (!temp && i == 1)
		{
			ft_putendl_fd("unset error: nothing to unset", 2);
			if (env)
				env->status = 1;
		}
		else if (temp)
		{
			env = ft_del_export(t[1], env);
			e = ft_del_env(t[1], e);
		}
	}
	return (env);
}
