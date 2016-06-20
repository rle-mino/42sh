/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script_cdt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 19:04:43 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/13 19:08:53 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_between_dhook(char **arg, int *i)
{
	int		save;
	char	*str;

	if (!arg || !arg[0])
		return (NULL);
	save = *i;
	while (arg[0][*i] && arg[0][*i] != '[')
		*i = *i + 1;
	if (!arg[0][*i] || arg[0][*i] != '[')
		return (NULL);
	*i = *i + 1;
	save = *i;
	while (*i < 1 || (arg[0][*i] && arg[0][*i - 1] != ']' && arg[0][*i] != ']'))
		*i = *i + 1;
	if (!arg[0][*i] || !ft_isspace(arg[0][*i - 1]))
	{
		ft_putstr_fd("42sh: [: ']' expected\n", 2);
		return (NULL);
	}
	str = ft_strsub(arg[0], save + 1, *i - save - 1);
	if (!str)
		malloc_handling();
	*i = save + 1;
	return (ft_cmdsplit_dquote(str));
}

int			check_cdt(t_e **e, char **str, int i, int ret)
{
	char	**hook;
	int		newret;

	hook = get_between_dhook(str, &i);
	if (!hook || (hook[0] && !hook[1]))
		return (ret);
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
	(*e)->op = get_op_hook(str, i);
	if ((*e)->op == -1)
		return (ret);
	return (check_cdt(e, str, i, ret));
}
