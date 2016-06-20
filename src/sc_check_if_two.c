/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_check_if_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 21:18:28 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 21:15:12 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_then_fi_present(char **arg)
{
	if (!arg || !arg[0])
		return (0);
	if (!arg[1])
	{
		ft_putstr_fd("42sh: missing `then'\n", 2);
		return (0);
	}
	if (!arg[2])
	{
		ft_putstr_fd("42sh: missing `fi'\n", 2);
		return (0);
	}
	return (1);
}

int				check_then_fi_helper(int nb_then, int check)
{
	if ((check - nb_then) < 0)
	{
		ft_putstr_fd("42sh: missing `fi'\n", 2);
		return (0);
	}
	return (1);
}
