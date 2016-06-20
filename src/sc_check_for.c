/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_check_for.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 00:01:07 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 21:21:22 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_method_for_error(char **arg)
{
	int		i;

	i = 0;
	while (arg[0] && arg[0][i])
	{
		if (arg[0][i] == '`')
		{
			i++;
			while (arg[0][i] && arg[0][i] != '`')
				i++;
			if (!arg[0][i] || !arg[0][i + 1])
				return (0);
			i++;
		}
		if (!ft_isspace(arg[0][i]) && !ft_isalnum(arg[0][i]))
		{
			ft_putstr_fd("42sh: parse error near `", 2);
			ft_putchar_fd(arg[0][i], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		check_method_for_one(char **arg)
{
	char	**elem;
	int		i;
	int		save;

	save = 0;
	i = 2;
	elem = ft_cmdsplit(arg[0]);
	if (!elem || !elem[0] || !elem[1] || !elem[2])
		return (0);
	while (elem[i])
	{
		if (ft_strcmp(elem[i], "in") == 0)
			save = i;
		i++;
	}
	ft_tabdel(elem);
	if (save == 0)
		return (0);
	return (1);
}

static int		cmft_in_par(char **arg, int i)
{
	i = 0;
	if (!arg || !arg[0] || !arg[1] || !arg[2])
		return (-1);
	while (arg[2][i] && arg[2][i] != ')')
		i++;
	if (!arg[2][i] || !arg[2][i + 1] || arg[2][i + 2])
	{
		ft_putstr_fd("42sh: missing parenthesis\n", 2);
		return (0);
	}
	if (arg[2][i] == ')' && arg[2][i + 1] == ')' && arg[2][i + 2] == 0)
		return (1);
	ft_putstr_fd("42sh: missing parenthesis\n", 2);
	return (0);
}

static int		check_method_for_two(char **arg)
{
	int		i;

	i = 3;
	while (arg[0] && arg[0][i] && ft_isspace(arg[0][i]))
		i++;
	if (!arg[0][i] || !arg[0][i + 1])
	{
		ft_putstr_fd("42sh: wrong `for' structure\n", 2);
		return (0);
	}
	if (arg[0][i] == '(' && arg[0][i + 1] == '(')
		return (cmft_in_par(arg, i + 2));
	return (-1);
}

int				check_method_for(char **arg)
{
	int			ret;

	if (check_method_for_one(arg))
	{
		if (check_method_for_error(arg))
			return (0);
		return (1);
	}
	ret = check_method_for_two(arg);
	if (ret == 1)
		return (2);
	else if (ret == -1)
		return (-1);
	return (0);
}
