/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_check_if_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 21:17:08 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 19:31:32 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_condition_if(char **arg, int i)
{
	static char		st_ctrl[12][4] = {"-eq", "-lt", "-gt", "-ge", "-le", "-ne",
										"!=", "=", "-f", "-z", "-r", "-w"};
	int				index;

	index = 0;
	while (index < 12 && arg && arg[i])
	{
		if (ft_strcmp(st_ctrl[index], arg[i]) == 0)
		{
			if (index <= 5)
				return (check_condition_num_if(arg, i));
			else if (index <= 7)
				return (check_condition_alpha_if(arg, i));
			return (check_condition_file_if(arg, i));
		}
		index++;
	}
	ft_putstr_fd("42sh: unknown condition: ", 2);
	ft_putendl_fd(arg[i], 2);
	return (0);
}

int				check_between_bracket_if_two(char **arg, int begin, int end)
{
	char		*str;
	char		**tabby;
	int			ret;

	ret = 1;
	str = ft_strsub(arg[0], begin + 1, end - begin - 1);
	if (!str)
		malloc_handling();
	tabby = ft_cmdsplit_dquote(str);
	if (!tabby)
		malloc_handling();
	ft_strdel(&str);
	if (tabby[0] && tabby[1] && tabby[2] && tabby[3])
		ret += error_bracket_if();
	else if (tabby[0] && !tabby[1])
		ret += 1;
	else if (!check_condition_if(tabby, 1))
		ret -= 1;
	ft_tabdel(tabby);
	return (ret);
}

int				check_between_bracket_if(char **arg, int begin, int end)
{
	int			ret;
	int			i;
	int			save;

	i = begin + 1;
	ret = check_between_bracket_if_two(arg, begin, end);
	if (ret <= 0)
		return (0);
	while (arg[0][i] && arg[0][i] != '[')
		i++;
	if (arg[0][i] == '[')
	{
		save = i;
		while (arg[0][i] && arg[0][i] != ']')
			i++;
		if (arg[0][i] && arg[0][i] == ']')
			return (check_between_bracket_if(arg, save, i));
	}
	return (1);
}

int				check_method_two_if(t_e *e, char **arg, int i)
{
	int			save;
	char		*var;

	save = i;
	if ((var = ft_strchr(arg[0], '$')) != NULL)
		replace_var(&e, &(arg[0]), ft_strdup(var + 1), 0);
	if (ft_strchr(arg[0], '`') != NULL)
		arg[0] = ft_replace_back_quote(arg[0], e);
	if (!ft_isspace(arg[0][i + 1]))
	{
		ft_putstr_fd("42sh: bad pattern: ", 2);
		ft_putchar_fd(arg[0][i], 2);
		ft_putchar_fd(arg[0][i + 1], 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	while (arg[0][i] && arg[0][i] != ']')
		i++;
	if (!arg[0][i] || !ft_isspace(arg[0][i - 1]))
	{
		ft_putstr_fd("42sh: [: ']' expected\n", 2);
		return (0);
	}
	return (check_between_bracket_if(arg, save, i));
}

int				check_method_if(t_e *e, char **arg)
{
	int			i;

	i = 2;
	if (!arg || !arg[0])
		return (0);
	while (arg[0][i] && ft_isspace(arg[0][i]))
		i++;
	if (arg[0][i] == '[')
		return (check_method_two_if(e, arg, i));
	else
		return (1);
	return (0);
}
