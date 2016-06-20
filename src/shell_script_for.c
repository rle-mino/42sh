/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script_for.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 00:00:04 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/06 16:29:21 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**create_var_for(char **arg)
{
	int		end;
	int		i;
	char	**tmp;
	char	**ret;

	tmp = ft_cmdsplit(arg[0]);
	end = 2;
	i = 1;
	while (tmp[end] && ft_strcmp("in", tmp[end]) != 0)
		end++;
	ret = (char**)ft_memalloc(sizeof(char*) * ((end - i) + 1));
	if (!ret)
		malloc_handling();
	while (i < end)
	{
		ret[i - 1] = ft_strdup(tmp[i]);
		if (!ret[i - 1])
			malloc_handling();
		i++;
	}
	ft_tabdel(tmp);
	return (ret);
}

char		**create_list_for(char **arg)
{
	int		begin;
	int		end;
	int		i;
	char	**tmp;
	char	**ret;

	i = 0;
	tmp = ft_cmdsplit(arg[0]);
	begin = 2;
	while (tmp[begin] && ft_strcmp("in", tmp[begin]) != 0)
		begin++;
	begin++;
	end = begin;
	while (tmp[end])
		end++;
	ret = (char**)ft_memalloc(sizeof(char*) * (end - begin + 1));
	if (!ret)
		malloc_handling();
	while (begin < end)
		ret[i++] = ft_strdup(tmp[begin++]);
	ft_tabdel(tmp);
	return (ret);
}

char		**create_newtab_for(char **arg, int *begin, int *i, int *stop)
{
	char	**newtab;

	newtab = (char**)ft_memalloc(sizeof(char*) * (*i + 1));
	while (*begin < (*i - 1))
	{
		if (*begin == 0)
			newtab[*begin] = ft_strdup(arg[*begin + 1] + 3);
		else
			newtab[*begin] = ft_strdup(arg[*begin + 1]);
		*begin = *begin + 1;
	}
	*stop = *begin;
	*i = *i + 1;
	return (newtab);
}

char		**delete_for(char **arg, int *stop)
{
	char	**tmp;
	char	**newtab;
	int		i;
	int		begin;
	int		max;

	begin = 0;
	i = 1;
	tmp = arg;
	while (arg[i] && ft_strncmp(arg[i], "for", 3) != 0)
		i++;
	max = i;
	while (i)
	{
		if (arg[i] && ft_strncmp(arg[i], "done", 4) == 0)
			break ;
		i--;
	}
	newtab = create_newtab_for(arg, &begin, &i, stop);
	return (newtab);
}

int			do_for_script(t_e **e, char **arg)
{
	int		method;
	int		i;

	i = 1;
	method = check_method_for(arg);
	if (method != -1 && method != 0)
	{
		if (!check_do_done(arg))
			method = 0;
	}
	if (method == 1)
	{
		do_for_first_method(e, arg);
		return (1);
	}
	else if (method == 2)
	{
		ft_putstr_fd("not implemented yet\n", 2);
	}
	else if (method == -1)
		ft_putstr_fd("42sh: missing some parameters\n", 2);
	return (0);
}
