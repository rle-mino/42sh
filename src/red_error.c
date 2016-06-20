/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 14:47:24 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/17 14:24:28 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		is_empty(char *s)
{
	int		i;

	i = -1;
	if (!s)
		return (0);
	while (s && s[++i])
		if (!ft_isspace(s[i]))
			return (0);
	return (1);
}

int		is_redir(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int		print_red_error(char *s, int i, int check)
{
	if (check < 0)
	{
		if (check == -1)
			ft_putendl_fd("42sh: ambiguous output redirect", 2);
		else
			ft_putendl_fd("42sh: null argument between redirection", 2);
		return (-1);
	}
	ft_putstr_fd("42sh: parse error near `", 2);
	if (i == -1)
	{
		ft_putchar_fd(s[0], 2);
		if (s[1] && s[1] == s[0])
			ft_putchar_fd(s[0], 2);
	}
	else
	{
		ft_putchar_fd(s[i - check], 2);
		if (s[i - check + 1] == s[i - check])
			ft_putchar_fd(s[i - check + 1], 2);
	}
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int		csh_error(char *s, int i, int n, char c)
{
	int		check;
	char	*tmp;

	if (c > '>')
		c = '|';
	if (n < 0 || n > 2)
		return (n);
	tmp = no_char(s, c);
	check = 0;
	while (s && !ft_strequ(tmp, s) && tmp[++i] && n < 3 && ++check)
	{
		if ((check_empty(tmp, i, check) == 1 && is_redir(tmp[i]) == 1
				&& ((tmp[i] == c && c != '|'))) || (tmp[i] == '<' && c == '|'))
			return (-1);
		if (check_empty(tmp, i, check) == 1 && is_redir(tmp[i]) == 1)
			return (-2);
		else if (check > 0 && is_redir(tmp[i] == 1))
		{
			if (ft_strequ(no_char(tmp, c), tmp))
				break ;
			tmp = no_char(tmp, c);
			check = 0;
		}
	}
	return (csh_error(s, -1, n + 1, c + 2));
}

int		red_error(t_e *env, char *s, int i)
{
	int		j;
	int		check;

	if (ft_err_red(env, s, -1) == -1)
		return (-1);
	if ((j = csh_error(s, -1, 0, '<')) < 0)
		return (print_red_error(s, 0, j));
	if (s && is_redir(s[0]) == 1 && (!s[1] || s[1] != '&'))
		return (print_red_error(s, -1, 0));
	while (s && s[++i])
	{
		check = 0;
		while (s[i] && is_redir(s[i]) == 1)
		{
			i++;
			check++;
			j = i;
			while (s[j] && (s[j] == ' ' || s[j] == '\t'))
				j++;
			if (((!s[j] || s[j] == ';') && s[i] == '|') || check > 2
					|| (check == 2 && (s[i - 1] != s[i - 2] || s[i] == '|')))
				return (print_red_error(s, i, check));
		}
	}
	return (1);
}
