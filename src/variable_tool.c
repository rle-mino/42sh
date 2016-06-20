/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:20:42 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/20 09:18:11 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_varcmp(char *var, char *env)
{
	int			i;

	i = 0;
	while (var[i] && env[i])
	{
		if (var[i] != env[i])
			return (0);
		i++;
	}
	if (!env[i] || env[i] != '=')
		return (0);
	return (1);
}

int				ft_varncmp(char *var, char *env, int max)
{
	int			i;

	i = 0;
	while (var[i] && env[i] && i < max)
	{
		if (var[i] != env[i])
			return (0);
		i++;
	}
	if (!env[i] || env[i] != '=')
		return (0);
	return (1);
}

int				check_inc(char *var)
{
	int			i;

	i = 0;
	while (var[i])
		i++;
	i -= 2;
	if (!ft_strncmp(var + i, "++", 2))
		return (1);
	if (!ft_strncmp(var + i, "--", 2))
		return (2);
	return (0);
}

static char		*inc_str(char *var, int inc, t_e **e, char *name)
{
	int			a;
	char		*ret;
	int			max;
	char		*del;
	char		*tmp;

	if (!var || !name)
		return (NULL);
	if (!ft_isnum(var))
		return (var);
	max = ft_strlen(name) - 2;
	ft_strclr(&name[max]);
	if (inc == 1)
		a = ft_atoi(var) + 1;
	else
		a = ft_atoi(var) - 1;
	ret = ft_itoa(a);
	del = ft_strjoin(name, "=");
	tmp = del;
	del = ft_strjoin(del, ret);
	ft_strdel(&tmp);
	*e = add_env_overwrite(*e, del, name);
	ft_strdel(&var);
	ft_strdel(&del);
	return (ret);
}

char			*inc_var(char *var, int inc, t_e **e)
{
	t_export	*tmp;
	char		*str;
	int			len;

	str = NULL;
	if (!e || !var || !*e)
		return (NULL);
	len = ft_strlen(var) - 2;
	tmp = (*e)->export;
	while (tmp)
	{
		if (ft_varncmp(var, tmp->export_env, len))
		{
			if ((str = ft_strchr(tmp->export_env, '=')) != NULL)
				str = ft_strdup(str + 1);
			str = inc_str(str, inc, e, var);
			return (str ? str : ft_strdup(tmp->export_env));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
