/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script_until.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 16:14:27 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/13 17:48:25 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**create_in_until_while(char **arg, int i, int ctrl)
{
	int		max;
	char	**newarg;
	int		id;

	id = 0;
	find_correspondant(arg, 0, -2);
	max = find_correspondant(arg, 0, ctrl);
	newarg = (char**)ft_memalloc(sizeof(char*) * (max + 1));
	if (!newarg)
		malloc_handling();
	newarg[id] = ft_strdup(arg[i++] + 3);
	if (!newarg[id])
		malloc_handling();
	id++;
	while (id < (max - 1))
	{
		newarg[id] = ft_strdup(arg[i]);
		if (!newarg[id])
			malloc_handling();
		i++;
		id++;
	}
	return (newarg);
}

int			do_in_until(t_e **e, char **arg)
{
	char	**newarg;
	int		i;

	i = 0;
	newarg = create_in_until_while(arg, 1, UNTIL);
	if (!newarg)
		return (0);
	while (newarg && newarg[i])
	{
		*e = ft_exec_cmd(newarg[i], *e, -1);
		i++;
	}
	ft_tabdel(newarg);
	return (1);
}

int			do_until_script(t_e **e, char **arg)
{
	if (!check_until(arg))
		return (0);
	*e = ft_exec_cmd(ft_strdup(arg[0] + 5), *e, -1);
	while ((*e)->status != 0)
	{
		do_in_until(e, arg);
		*e = ft_exec_cmd(ft_strdup(arg[0] + 5), *e, -1);
	}
	return (1);
}
