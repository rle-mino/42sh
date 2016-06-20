/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 22:40:23 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 17:22:55 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_structure_controle(char *ctrl)
{
	int		i;

	if (!ctrl)
		return (0);
	i = 0;
	while (ctrl[i] && ft_isspace(ctrl[i]))
		i++;
	if (ft_strncmp(ctrl + i, "if", 2) == 0 && ft_isspace(ctrl[2 + i]))
		return (IF);
	if (ft_strncmp(ctrl + i, "elif", 4) == 0 && ft_isspace(ctrl[4 + i]))
		return (IF);
	if (ft_strncmp(ctrl + i, "case", 4) == 0 && ft_isspace(ctrl[4 + i]))
		return (CASE);
	return (0);
}

static int	check_do_done_helper(char **arg)
{
	if (!arg[0] || !arg[1] || !arg[2])
	{
		if (arg[0] && !arg[1])
			ft_putstr_fd("42sh: missing `do'\n", 2);
		else if (arg[0] && arg[1])
			ft_putstr_fd("42sh: missing `done'\n", 2);
		else
			ft_putstr_fd("42sh: missing `do' and `done'\n", 2);
		return (0);
	}
	return (1);
}

static void	check_do_done_helper_two(char **arg, int *nb_do, int *check)
{
	int				i;
	int				id;

	id = 0;
	i = 2;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i][id]))
			id++;
		if (ft_strncmp(arg[i] + id, "do", 2) == 0 && ft_isspace(arg[i][2 + id]))
			*nb_do = *nb_do + 1;
		if (ft_strncmp(arg[i] + id, "done", 4) == 0 && !arg[i][4 + id])
			*check = *check + 1;
		id = 0;
		i++;
	}
}

int			check_do_done(char **arg)
{
	int				i;
	int				check;
	int				nb_do;

	nb_do = 1;
	check = 0;
	i = 0;
	if (!check_do_done_helper(arg))
		return (0);
	while (ft_isspace(arg[1][i]))
		i++;
	if (!(ft_strncmp(arg[1] + i, "do", 2) == 0 && ft_isspace(arg[1][2 + i])))
	{
		ft_putstr_fd("42sh: parse error near `done'\n", 2);
		return (0);
	}
	check_do_done_helper_two(arg, &nb_do, &check);
	if ((check - nb_do) < 0)
	{
		ft_putstr_fd("42sh: missing `done'\n", 2);
		return (0);
	}
	return (1);
}

int			is_script(char **arg)
{
	int				selected;

	selected = 0;
	if (!arg || !arg[0])
	{
		ft_putstr_fd("42sh: missing command\n", 2);
		return (0);
	}
	if ((selected = is_structure_boucle(arg[0])) > 0)
		return (selected);
	if ((selected = is_structure_controle(arg[0])) > 0)
		return (selected);
	return (0);
}
