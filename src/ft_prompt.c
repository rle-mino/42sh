/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:50:09 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/19 13:59:21 by jaubard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "colors.h"

void			print_username(t_e *env)
{
	char		*s;
	t_e			*temp;

	temp = env;
	while (temp)
	{
		if (ft_start_str("USER=", temp->str) == 1)
			break ;
		temp = temp->next;
	}
	if (!temp)
		ft_putstr_fd("void", get_fd(-1));
	else
	{
		s = no_char(temp->str, '=');
		if (s[0] != '\0')
			ft_putstr_fd(s, get_fd(-1));
		else
			ft_putstr_fd("void", get_fd(-1));
	}
}

static int		check_cwd(char *cwd, t_e *home)
{
	int			i;

	if (!cwd || !home)
		return (-1);
	i = ft_strlen(home->str + 5);
	if (i > (int)ft_strlen(cwd))
		return (-1);
	if (ft_start_str(home->str + 5, cwd)
			|| ft_start_str(home->str + 5, cwd + i))
		return (i);
	return (-1);
}

void			ft_putstrcolor_fd(char *cwd, int fd)
{
	int			i;
	int			limit;

	i = 0;
	limit = 0;
	if (!cwd)
		return ;
	while (cwd[i])
	{
		if (cwd[i] == '/')
			limit = i;
		i++;
	}
	i = 0;
	while (cwd[i])
	{
		ft_putchar_fd(cwd[i], fd);
		if (i == limit)
			ft_putstr_fd(C_CYAN, fd);
		i++;
	}
	ft_putstr_fd("\033[0m", fd);
}

void			print_cwd(t_e *env)
{
	char		*cwd;
	char		*cmp;
	t_e			*temp;
	int			off;

	temp = env;
	while (temp && ft_start_str("HOME=", temp->str) != 1)
		temp = temp->next;
	if (!(cwd = get_any_env_var(&env, "PWD")))
	{
		ft_putchar_fd('.', get_fd(-1));
		return ;
	}
	off = check_cwd(cwd, temp);
	if (off != -1 && temp)
	{
		cmp = temp->str + 5;
		ft_putchar_fd('~', get_fd(-1));
		ft_putstrcolor_fd(cwd + off, get_fd(-1));
	}
	else
		ft_putstrcolor_fd(cwd, get_fd(-1));
	ft_putchar_fd(' ', get_fd(-1));
	ft_strdel(&cwd);
}
