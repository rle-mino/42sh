/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_first_method_if_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 21:24:01 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 19:30:48 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**get_cmd_ret(t_e **e, char **arg)
{
	int			i;

	i = 0;
	while (arg[0][i] && arg[0][i] != '[')
		i++;
	if (arg[0][i])
	{
		i++;
		while (arg[0][i] && arg[0][i] != ']')
			i++;
		if (arg[0][i])
			return (NULL);
	}
	*e = ft_exec_cmd(arg[0] + 2, *e, -1);
	return (NULL);
}

char			**get_between_hook(t_e **e, char **arg, int *i)
{
	int			save;
	char		*str;

	if (!arg || !arg[0])
		return (NULL);
	save = *i;
	while (arg[0][*i] && arg[0][*i] != '[')
		*i = *i + 1;
	if (!arg[0][*i])
		return (get_cmd_ret(e, arg));
	save = *i;
	while (arg[0][*i] && arg[0][*i] != ']')
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

int				get_op_hook(char **av, int i)
{
	while (av[0][i] && av[0][i] != ']')
		i++;
	while (av[0][i] && av[0][i] != '[' && av[0][i] != '&' && av[0][i] != '|')
		i++;
	if (av[0][i] && av[0][i + 1] && av[0][i] == '&' && av[0][i + 1] == '&')
		return (AND);
	else if (av[0][i] && av[0][i + 1] && av[0][i] == '|' && av[0][i + 1] == '|')
		return (OR);
	if (!av[0][i])
		return (0);
	ft_putstr_fd("42sh: unknown operand :", 2);
	ft_putchar_fd(av[0][i], 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int				test_file_if(t_e *e, char **hook)
{
	struct stat	s;

	if (!hook[0] || !hook[1] || stat(hook[1], &s) == -1)
		return (1);
	else if (ft_strcmp(hook[0], "-f") == 0)
	{
		if (S_ISREG(s.st_mode))
			return (0);
	}
	else if (ft_strcmp(hook[0], "-z") == 0)
	{
		if (get_any_env_var(&e, hook[1]))
			return (0);
	}
	else if (ft_strcmp(hook[0], "-r") == 0)
	{
		if (s.st_mode & S_IRUSR)
			return (0);
	}
	else if (ft_strcmp(hook[0], "-w") == 0)
	{
		if (s.st_mode & S_IWUSR)
			return (0);
	}
	return (1);
}

int				test_cdt_num_if(char **hook)
{
	int			a;
	int			b;

	a = ft_atoi(hook[0]);
	b = ft_atoi(hook[2]);
	if (ft_strcmp(hook[1], "-eq") == 0 && a == b)
		return (0);
	else if (ft_strcmp(hook[1], "-lt") == 0 && a < b)
		return (0);
	else if (ft_strcmp(hook[1], "-gt") == 0 && a > b)
		return (0);
	else if (ft_strcmp(hook[1], "-le") == 0 && a <= b)
		return (0);
	else if (ft_strcmp(hook[1], "-ge") == 0 && a >= b)
		return (0);
	else if (ft_strcmp(hook[1], "-ne") == 0 && a != b)
		return (0);
	return (1);
}
