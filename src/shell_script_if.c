/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 16:22:33 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 22:28:29 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_elif(char **arg)
{
	int			i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	while (arg[0][i] && ft_isspace(arg[0][i]))
		i++;
	if (arg[0] && arg[0][i] && ft_strncmp(arg[0] + i, "elif", 4) == 0)
		return (1);
	return (0);
}

int				find_elif(char **arg, int i)
{
	int			id;

	if (!arg || !arg[0])
		return (0);
	id = 0;
	while (arg[i])
	{
		while (arg[i][id] && ft_isspace(arg[i][id]))
			id++;
		if (ft_strncmp(arg[i] + id, "fi", 2) == 0)
			return (-1);
		if (ft_strncmp(arg[i] + id, "elif", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int				cdt_find_corr(char **str, int i)
{
	int			a;

	a = 0;
	if (!str || !*str)
		return (0);
	while (str[i][a] && ft_isspace(str[i][a]))
		a++;
	if (ft_strncmp("if", str[i] + a, 2) != 0)
	{
		if (ft_strncmp("then", str[i] + a, 4) == 0)
		{
			a += 4;
			while (str[i][a] && ft_isspace(str[i][a]))
				a++;
			if (!ft_strncmp("if", str[i] + a, 2) &&
			find_correspondant(str, i, IF) == -1)
				return (1);
		}
		return (0);
	}
	else if (find_correspondant(str, i, IF) == -1)
		return (1);
	return (0);
}

int				do_if_script(t_e **e, char **arg)
{
	int			method;
	int			i;
	int			id;

	id = 0;
	i = 0;
	(*e)->op = 0;
	method = check_method_if(*e, arg);
	if (method > 0 && !check_then_fi(arg))
		return (0);
	if (method == 1)
	{
		if (!do_if_fmethod(e, arg, 0, -1))
			do_in_if_fmethod(e, arg);
		else if ((i = find_elif(arg, id)) != -1 &&
		!do_if_fmethod(e, arg + i, 0, -1))
			do_in_if_fmethod(e, arg + i);
		return (1);
	}
	return (0);
}
