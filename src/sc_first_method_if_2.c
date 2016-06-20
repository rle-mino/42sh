/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_first_method_if_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 21:24:01 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 21:24:05 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			do_if_fmethod(t_e **e, char **arg, int i, int ret)
{
	char	**hook;
	int		newret;

	hook = get_between_hook(e, arg, &i);
	if (!hook)
		return ((*e)->status);
	newret = get_ret_hook(e, hook);
	if (ret != -1 && (*e)->op == OR && (ret == 0 || newret == 0))
		ret = 0;
	else if (ret != 1 && (*e)->op == OR)
		ret = 1;
	if (ret != -1 && (*e)->op == AND && (ret == 0 && newret == 0))
		ret = 0;
	else if (ret != -1 && (*e)->op == AND)
		ret = 1;
	if (ret == -1)
		ret = newret;
	(*e)->op = get_op_hook(arg, i);
	if ((*e)->op == -1)
		return (ret);
	(*e)->status = ret;
	return (do_if_fmethod(e, arg, i, ret));
}

int			check_then(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (ft_strncmp(str + i, "then", 4) == 0)
		return (i + 5);
	return (0);
}

int			do_then_if(t_e **e, char *str, char **arg)
{
	int		i;

	i = 2;
	*e = ft_exec_cmd(str, *e, -1);
	if (!arg || !arg[0] || !arg[1] || !arg[2])
		return (0);
	while (arg[i])
	{
		*e = ft_exec_cmd(arg[i], *e, -1);
		i++;
	}
	return (1);
}

char		**recreate_if_tab(char **arg)
{
	int		i;
	int		max;
	char	**newtab;
	int		id;

	id = 0;
	find_correspondant(arg, 0, -2);
	max = find_correspondant(arg, 0, IF) - 1;
	i = 1;
	newtab = (char**)ft_memalloc(sizeof(char*) * (max + 1));
	if (!newtab)
		return (NULL);
	newtab[id++] = ft_strdup(arg[1] + check_then(arg[1]));
	while (i < max)
	{
		newtab[id] = ft_strdup(arg[id + 1]);
		id++;
		i++;
	}
	return (newtab);
}

int			do_in_if_fmethod(t_e **e, char **arg)
{
	char	**tmp;
	int		max;

	max = 0;
	tmp = recreate_if_tab(arg);
	if (!tmp)
		return (0);
	while (tmp[max])
		max++;
	if (do_while_in_if(e, tmp, max, arg) == 0)
		return (1);
	ft_tabdel(tmp);
	return (1);
}
