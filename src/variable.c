/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 22:43:34 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 22:55:01 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_any_local_var(t_e **e, char *var)
{
	t_export	*tmp;
	char		*str;
	int			inc;

	str = NULL;
	if (!e || !*e || !var)
		return (NULL);
	if ((inc = check_inc(var)))
		return (inc_var(var, inc, e));
	tmp = (*e)->export;
	while (tmp)
	{
		if (ft_varcmp(var, tmp->export_env))
		{
			if ((str = ft_strchr(tmp->export_env, '=')) != NULL)
				str = ft_strdup(str + 1);
			return (str ? str : ft_strdup(tmp->export_env));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char			*get_any_env_var(t_e **e, char *var)
{
	int			i;
	t_e			*tmp;
	char		*str;

	i = 0;
	tmp = *e;
	while (var[i] && !ft_isspace(var[i]) && var[i] != '$')
		i++;
	if (!var[i] || var[i] == '$')
		ft_strclr(var + i);
	if (var[0] == '?' && !var[1])
		return ((*e)->status ? ft_strdup("1") : ft_strdup("0"));
	while (tmp)
	{
		if (ft_varcmp(var, tmp->str))
		{
			if ((str = ft_strchr(tmp->str, '=')) != NULL)
				str = ft_strdup(str + 1);
			return (str ? str : ft_strdup(tmp->str));
		}
		tmp = tmp->next;
	}
	if ((str = get_any_local_var(e, var)) != NULL)
		return (str);
	return (NULL);
}

char			*join_delete_var(char *str, int begin, int end, char *result)
{
	char		*one;
	char		*two;
	char		*three;
	char		*ret;
	int			i;

	ret = NULL;
	one = NULL;
	two = NULL;
	i = 0;
	while (str[i])
		i++;
	if (begin > 0)
	{
		one = ft_strsub(str, 0, begin - 1);
		two = ft_strsub(str, end, i - end);
		three = result ? ft_strjoin(one, result) : NULL;
		ret = three ? ft_strjoin(three, two) : ft_strjoin(one, two);
		ft_strdel(&one);
		ft_strdel(&two);
		if (three)
			ft_strdel(&three);
	}
	ft_strdel(&result);
	return (ret ? ret : ft_strdup(" "));
}

char			*cut_and_replace_var(char *str, char *result, int i)
{
	int			begin;
	int			end;

	begin = 0;
	end = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!begin)
				begin = i + 1;
			i++;
			while (str[i] && !ft_isspace(str[i]) && str[i] != '$'
			&& str[i] != 34)
				i++;
			if (!end)
				end = i;
			if (!str[i])
				break ;
		}
		i++;
	}
	return (join_delete_var(str, begin, end, result));
}

void			replace_var(t_e **e, char **str, char *var, int i)
{
	char		*result;
	char		*varnew;
	char		*tmp;
	char		*newvar;
	int			a;

	a = 0;
	if (!var || !str || !*str || !**str)
		return ;
	while (var[a] && !ft_isspace(var[a]) && var[a] != 34)
		a++;
	newvar = ft_strsub(var, 0, a);
	result = get_any_env_var(e, newvar);
	ft_strdel(&var);
	ft_strdel(&newvar);
	tmp = *str;
	*str = cut_and_replace_var(*str, result, i == -1 ? 0 : i);
	if ((varnew = ft_strchr(*str, '$')) != NULL && !back_strchr(*str, 39))
		replace_var(e, str, ft_strdup(varnew + 1), 0);
}
