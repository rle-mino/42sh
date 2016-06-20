/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_check_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 16:37:57 by ishafouz          #+#    #+#             */
/*   Updated: 2016/06/17 21:18:37 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				error_bracket_if(void)
{
	ft_putstr_fd("42sh: [: too many arguments\n", 2);
	return (-1);
}

int				ft_isnum(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				check_condition_num_if(char **arg, int i)
{
	if (i == 0 || !arg[i + 1] || !ft_isnum(arg[i + 1]) || !ft_isnum(arg[i - 1]))
	{
		ft_putstr_fd("42sh: integer expression expected\n", 2);
		return (0);
	}
	return (10);
}

int				check_condition_alpha_if(char **arg, int i)
{
	if (i == 0 || !arg[i + 1] || !arg[i - 1])
	{
		ft_putstr_fd("42sh: expression expected\n", 2);
		return (0);
	}
	return (5);
}

int				check_condition_file_if(char **arg, int i)
{
	if (i != 0 || !arg[i + 1])
	{
		ft_putstr_fd("42sh: parse error: expected two arguments\n", 2);
		return (0);
	}
	return (1);
}
