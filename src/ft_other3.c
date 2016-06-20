/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 11:33:21 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/04 14:20:28 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		check_pfd(char *s)
{
	int		i;
	int		check;

	i = -1;
	check = 0;
	if (!s || !s[0])
		return (-1);
	if (ft_strequ("", s))
		return (0);
	while (s && s[++i])
		if (ft_isalpha(s[i]))
			check = 1;
	return (check + 1);
}

int		fuck_la_norme(char *s)
{
	int		i;

	i = 0;
	while (s && s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	while (s && s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	return (i);
}

void	oops_i_did_it_again(char *s, int i, int j)
{
	if (s && s[i])
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putnbr_fd(j, 2);
		ft_putendl_fd(" bad file descriptor", 2);
	}
	else
	{
		ft_putstr_fd("42sh: parse error with the redirected file: ", 2);
		ft_putendl_fd(s, 2);
	}
}

int		*get_special_fd(char *s, int *file)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!s || !s[0])
	{
		file[0] = -1;
		return (file);
	}
	tmp = ft_cmdsplit(s);
	if (!tmp || !tmp[0])
	{
		file[0] = 1;
		return (file);
	}
	while (tmp && tmp[0][i] && ft_isdigit(tmp[0][i]))
		i++;
	file = ret_special_fd(file, tmp[0], i);
	if (file[0] < 0 || (!tmp[0][i] && file[0] > 2))
		oops_i_did_it_again(tmp[0], i, file[0]);
	ft_tabdel(tmp);
	ft_strdel(&s);
	return (file);
}

int		central_fiction(char **t)
{
	ft_tabdel(t);
	ft_putendl_fd("42sh: parse error near `&'", 2);
	return (-1);
}
