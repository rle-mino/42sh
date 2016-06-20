/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:14:29 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/12 12:37:10 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

bool	check_r2(char c)
{
	if (!c || (c != '&' && c != '-' && c != '<'
				&& c != '0' && c != '1' && c != '2' && c != '>'))
		return (false);
	return (true);
}

int		check_r(char *s)
{
	int		i;
	bool	check;

	i = -1;
	check = false;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			if (!s[i + 1] || (s[i + 1] && s[i + 1] != '&'
				&& s[i + 1] < '0' && s[i + 1] > '2') || check)
				return (-1);
			check = true;
		}
		else if (s[i] >= '0' && s[i] <= '2' && i != 0 && !check)
			return (-1);
		else if (s[i] == '&' && s[i + 1]
				&& s[i + 1] != '-' && s[i + 1] < '0' && s[i + 1] > '2')
			return (-1);
		else if (!check_r2(s[i]))
			return (-1);
	}
	return (1);
}

t_e		*close_red(char *s, int *red, int fd, t_e *env)
{
	ft_strdel(&s);
	ft_close_red(red, fd);
	return (env);
}

t_e		*clean_red(char *s, char **t, t_e *env)
{
	ft_strdel(&s);
	ft_tabdel(t);
	return (env);
}

char	*cmd_redirless2(char *s)
{
	if (back_strchr(s, '>') != NULL)
		return (ft_str_trunc(s, '>'));
	else
		return (ft_str_trunc(s, '<'));
}
