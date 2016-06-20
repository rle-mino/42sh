/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_tools_for.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 14:09:55 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/04 16:17:29 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						max_tab(char **var, char **list)
{
	int					i;
	int					max;

	max = 0;
	i = 0;
	while (var[i])
		i++;
	max = i;
	i = 0;
	while (list[i])
		i++;
	if (i > max)
		return (i);
	return (max);
}

t_e						*search_env(t_e *e, char *var)
{
	int					len;
	t_e					*tmp;

	tmp = e;
	if (!var || !tmp)
		return (NULL);
	len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->str, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_export				*search_local(t_e *e, char *var)
{
	int					len;
	t_export			*tmp;

	if (!e)
		return (NULL);
	tmp = e->export;
	if (!var || !tmp)
		return (NULL);
	len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->export_env, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_e						*add_env_overwrite(t_e *e, char *s, char *var)
{
	t_e					*tmp;
	t_export			*tmp_exp;

	tmp = search_env(e, var);
	if (!tmp && e)
	{
		tmp_exp = search_local(e, var);
		if (!tmp_exp)
			e->export = ft_add_export(e->export, s, 0);
		else
		{
			ft_strdel(&(tmp_exp->export_env));
			tmp_exp->export_env = ft_strdup(s);
		}
	}
	else if (tmp)
	{
		ft_strdel(&(tmp->str));
		tmp->str = ft_strdup(s);
	}
	return (e);
}
