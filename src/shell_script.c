/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 22:40:32 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 22:47:47 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**clean_arg_for(char **arg)
{
	int			i;
	int			end;
	char		**newtab;
	int			begin;

	begin = 0;
	i = 0;
	while (arg[i] && ft_strncmp(arg[i], "done", 4) != 0)
		i++;
	if (!arg[i])
		return (arg);
	end = i++;
	while (arg[end])
		end++;
	newtab = (char**)ft_memalloc(sizeof(char*) * (end - i + 1));
	if (!newtab)
		malloc_handling();
	while (arg[i])
	{
		newtab[begin] = ft_strdup(arg[i++]);
		begin++;
	}
	return (newtab);
}

t_e				*exec_next_script(t_e **e, char **arg)
{
	int			i;
	int			useless;
	int			newctrl;
	char		**tmp;

	useless = 0;
	i = 0;
	while (arg[i])
	{
		if ((newctrl = is_script(arg + i)) > 0)
		{
			tmp = ft_cpy_tab(arg + i);
			*e = do_shell_script(e, tmp, newctrl);
			return (*e);
		}
		else
			*e = ft_exec_cmd(arg[i], *e, -1);
		i++;
	}
	return (*e);
}

pid_t			get_pid(pid_t pid)
{
	static pid_t	ret = -10;

	if (ret == -10)
		ret = pid;
	if (pid == -10)
		ret = -10;
	return (ret);
}

t_e				*do_shell_script(t_e **e, char **arg, int ctrl)
{
	pid_t		father;

	get_pid(-10);
	signal(SIGINT, &sc_handler);
	father = fork();
	if (father == 0)
	{
		do_in_shell_script(e, arg, ctrl);
	}
	else
	{
		get_pid(father);
		waitpid(father, &(*e)->status, 0);
	}
	signal(SIGINT, sig_handler);
	return (*e);
}

t_e				*do_in_shell_script(t_e **e, char **arg, int ctrl)
{
	if (ctrl == FOR)
	{
		if (!do_for_script(e, arg))
			ft_tabdel(arg);
		else
			arg = clean_arg_for(arg);
	}
	if (ctrl == IF)
	{
		if (!do_if_script(e, arg))
			ft_tabdel(arg);
	}
	if (ctrl == UNTIL)
	{
		if (!do_until_script(e, arg))
			ft_tabdel(arg);
	}
	if (ctrl == WHILE)
	{
		if (!do_while_script(e, arg))
			ft_tabdel(arg);
	}
	exit(0);
	return (*e);
}
