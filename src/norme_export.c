/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:36:07 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/06 16:25:11 by jaubard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_e			*export_env(t_e *e, char *key, char *val)
{
	char	*f;
	t_e		*tmp;

	if (!e || !key || !val)
		return (NULL);
	tmp = e;
	while (tmp)
	{
		if (ft_start_str(key, tmp->str))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		ft_strdel(&tmp->str);
		tmp->str = ft_strdup(val);
	}
	else
	{
		f = ft_strlink(key, val, '=');
		e = ft_add_e(e, f);
		ft_strdel(&f);
	}
	return (e);
}

t_export	*ft_export_temp2(t_export *e, char *s)
{
	char		*tmp;

	tmp = ft_strjoin(s, "''");
	e = ft_add_export(e, tmp, false);
	ft_strdel(&tmp);
	return (e);
}

t_e			*ft_norme_setexport(char *key, t_e *env)
{
	char		*s;
	char		*s2;

	s = ft_strjoin(key, "=");
	s2 = ft_strjoin(s, "''");
	ft_strdel(&s);
	env->export = ft_add_export(env->export, s2, true);
	env = export_env(env, key, "''");
	ft_strdel(&s2);
	return (env);
}

t_e			*ft_setexport3(t_e *tmp, t_e *env, t_export **temp)
{
	if (!tmp)
		env = ft_add_e(env, (*temp)->export_env);
	else
		env = export_env(env, tmp->str, (*temp)->export_env);
	(*temp)->display = true;
	return (env);
}

t_e			*ft_setexport2(t_e *env, t_export **temp, char *key)
{
	t_e			*tmp;

	while (*temp)
	{
		if (ft_start_str(key, (*temp)->export_env))
			break ;
		*temp = (*temp)->next;
	}
	if (!(*temp))
		env = ft_norme_setexport(key, env);
	else
	{
		tmp = env;
		key = ft_str_trunc((*temp)->export_env, '=');
		while (tmp)
		{
			if (ft_start_str(key, tmp->str))
				break ;
			tmp = tmp->next;
		}
		ft_strdel(&key);
		env = ft_setexport3(tmp, env, temp);
	}
	return (env);
}
