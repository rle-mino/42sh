/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 21:38:29 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/19 16:58:43 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

char			*get_git(char *pwd)
{
	static char		*ret = NULL;

	if (pwd && !ret)
		ret = ft_strdup(pwd);
	else if (pwd && ret)
	{
		ft_strdel(&ret);
		ret = ft_strdup(pwd);
	}
	return (ret);
}

void			print_git(t_e *e)
{
	char		*pwd;

	if (!e || !e->gitlen)
		return ;
	pwd = get_any_env_var(&e, "PWD");
	if (pwd && !ft_strncmp(pwd, get_git(NULL), e->gitlen))
	{
		ft_putstr_fd(C_BLUE, get_fd(-1));
		ft_putstr_fd("git(", get_fd(-1));
		ft_putstr_fd(C_RED, get_fd(-1));
		ft_putstr_fd("master", get_fd(-1));
		ft_putstr_fd(C_BLUE, get_fd(-1));
		ft_putstr_fd(") ", get_fd(-1));
	}
	else
	{
		ft_putstr_fd(C_RED, get_fd(-1));
		print_username(e);
		ft_putstr_fd(C_CYAN, get_fd(-1));
		ft_putstr_fd(" @ ", get_fd(-1));
	}
}
