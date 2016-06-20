/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_quote_tools_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 14:42:30 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/20 14:53:26 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err(int nb)
{
	if (nb == 0)
		ft_putstr_fd("42sh: parse error in command substitution\n", 2);
	return (0);
}

void		helper_back_quote(int fd[2], t_e *e, char *cmd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_exec_cmd(cmd, e, -1);
	exit(1);
}

int			check_back_quote(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '`')
		{
			i++;
			while (s[i] && s[i] != '`')
				i++;
			if (!s[i])
				return (0);
			if (s[i - 1] == '|')
				return (err(0));
		}
		i++;
	}
	return (1);
}
