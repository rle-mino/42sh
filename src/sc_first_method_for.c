/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_first_method_for.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 14:07:27 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 20:45:46 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		launch_for_fmethod_two(t_e **e, char **arg)
{
	char	**newcmd;
	int		selected;
	int		i;
	int		stop;

	stop = 0;
	i = 0;
	selected = 0;
	newcmd = delete_for(arg, &stop);
	if (!newcmd)
		return ;
	selected = is_script(newcmd);
	if (selected != 0)
		do_shell_script(e, newcmd, selected);
	else
	{
		while (newcmd[i] && i < stop)
			*e = ft_exec_cmd(newcmd[i++], *e, -1);
	}
}

void		launch_for_fmethod(t_e **e, char **arg, char **var, char **list)
{
	char	*tmp;
	char	*tmpfinal;
	int		i;
	int		id;
	int		max;

	max = max_tab(var, list);
	i = 0;
	while (max)
	{
		id = 0;
		while (var[id] && list[i])
		{
			tmp = ft_strjoin(var[id], "=");
			tmpfinal = ft_strjoin(tmp, list[i++]);
			*e = add_env_overwrite(*e, tmpfinal, var[id++]);
			ft_strdel(&tmp);
			ft_strdel(&tmpfinal);
		}
		launch_for_fmethod_two(e, arg);
		if (!list[i])
			break ;
		max--;
	}
}

void		do_for_first_method(t_e **e, char **arg)
{
	char	**list;
	char	**var;
	int		i;

	i = 0;
	if (ft_strchr(arg[0], '`') != NULL)
		arg[0] = ft_replace_back_quote(arg[0], *e);
	list = create_list_for(arg);
	var = create_var_for(arg);
	launch_for_fmethod(e, arg, var, list);
	ft_tabdel(list);
	ft_tabdel(var);
}
