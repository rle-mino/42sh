/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:18:00 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/08 17:18:29 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*** Add new variables in export
*/

t_e				*ft_add_export_second(char **t, int check, t_e *e)
{
	char		*s;
	char		*s2;

	if (!e || ft_strchr(t[1], '=') != NULL || ft_strchr(t[2], '=') != NULL)
		ft_putendl_fd("export: wrong arguments, arguments contain '='", 2);
	else if (!t[3]
			|| check == 0 || ft_strequ(t[3], "0") || ft_strequ(t[3], "1"))
	{
		s = ft_strjoin(t[1], "=");
		s2 = ft_strjoin(s, t[2]);
		e->export = ft_add_export(e->export, s2, true);
		e = export_env(e, t[1], t[2]);
		ft_strdel(&s);
		ft_strdel(&s2);
	}
	else if (ft_strequ("0", t[3]) == 0 && ft_strequ("1", t[3]) == 0)
		ft_putendl_fd("export error: bad overwrite value", 2);
	return (e);
}

/*
*** Change export variables if exists
*/

t_e				*ft_merge_env(t_e *e, char *key, char *v)
{
	t_e		*tmp;

	tmp = e;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_start_str(key, tmp->str))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		ft_strdel(&tmp->str);
		tmp->str = ft_strdup(v);
	}
	return (e);
}

t_e				*ft_change_export(t_e *env, char **t, t_export **mod, int check)
{
	char		*s;
	char		*new;

	if (ft_strchr(t[1], '=') != NULL || (t[2] && ft_strchr(t[2], '=') != NULL))
		ft_putendl_fd("export: wrong arguments, arguments contain '='", 2);
	else if (t && mod && *mod && (!t[3] || check == 0 || ft_strequ(t[3], "1")))
	{
		s = ft_strjoin(t[1], "=");
		new = ft_strjoin(s, t[2]);
		ft_strdel(&(*mod)->export_env);
		ft_strdel(&s);
		(*mod)->export_env = new;
		(*mod)->display = true;
		env = ft_merge_env(env, t[1], new);
	}
	else if (ft_strequ(t[3], "0") == 0)
		ft_putendl_fd("export error: bad overwrite value", 2);
	return (env);
}
