/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script_while.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 16:14:57 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/13 18:03:03 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			do_in_while(t_e **e, char **arg)
{
	char	**newarg;
	int		i;

	i = 0;
	newarg = create_in_until_while(arg, 1, WHILE);
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

int			do_while_script(t_e **e, char **arg)
{
	(*e)->status = 1;
	if (!check_while(arg))
		return (0);
	*e = ft_exec_cmd(ft_strdup(arg[0] + 5), *e, -1);
	while ((*e)->status == 0)
	{
		do_in_while(e, arg);
		*e = ft_exec_cmd(ft_strdup(arg[0] + 5), *e, -1);
	}
	return (1);
}
