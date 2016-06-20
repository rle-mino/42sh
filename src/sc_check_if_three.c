/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_check_if_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 21:14:06 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 22:29:09 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				error_missing(char *str)
{
	ft_putstr_fd("42sh: missing `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int				get_jump(int st)
{
	static int	ret = 0;

	if (st == -1)
		ret++;
	else if (st == -2)
		ret = 0;
	return (ret);
}

int				while_correspondant(char **arg, int i, int st, int to_jump)
{
	static char	st_ctrl[3][5] = {"done", "fi", "esac"};
	int			id;
	int			jump;
	int			len;

	len = 4;
	jump = 0;
	id = 0;
	if (st == 1)
		len = 2;
	while (arg[i])
	{
		while (arg[i][id] && ft_isspace(arg[i][id]))
			id++;
		if (arg[i][id] && !ft_strncmp(st_ctrl[st], arg[i] + id, len)
			&& !arg[i][id + len])
		{
			if (jump == to_jump)
				return (i);
			jump++;
		}
		id = 0;
		i++;
	}
	return (-1);
}

int				find_correspondant(char **arg, int i, int st)
{
	int			to_jump;
	int			ret;

	if (st > 0 && st <= 3)
		st = 0;
	if (st == 5)
		st = 1;
	if (st == 4)
		st = 2;
	to_jump = get_jump(st);
	if (st == -1 || st == -2 || i < 0)
		return (1);
	if ((ret = while_correspondant(arg, i, st, to_jump)) != -1)
	{
		find_correspondant(arg, 0, -1);
		return (ret);
	}
	return (-1);
}

int				check_then_fi(char **arg)
{
	int			i;
	int			nb_then;
	int			check;

	check = 0;
	nb_then = 1;
	i = 0;
	find_correspondant(arg, i, -2);
	if (check_then_fi_present(arg) == 0)
		return (0);
	while (arg[i])
	{
		if (cdt_find_corr(arg, i))
			return (error_missing("fi"));
		if ((!ft_strncmp("fi", arg[i], 2)))
			find_correspondant(arg, 0, -2);
		i++;
	}
	return (1);
}
