/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:25:09 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/04 15:38:23 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		ret_err(char **t)
{
	ft_tabdel(t);
	ft_putstr_fd("'\n'", 2);
	return (-1);
}

int		ret_ok(char **t)
{
	ft_tabdel(t);
	return (1);
}

t_e		*ret_err_redir(t_e *env)
{
	ft_putendl_fd("42sh: parse error near `&'", 2);
	return (env);
}

void	free_exec(char *s, char **t, char *s2, char **t2)
{
	ft_strdel(&s);
	ft_tabdel(t);
	ft_strdel(&s2);
	ft_tabdel(t2);
}

t_e		*ret_env_err(t_e *e, int status)
{
	if (e)
		e->status = status;
	return (e);
}
