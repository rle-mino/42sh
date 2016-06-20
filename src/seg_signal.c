/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 20:51:27 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/02 21:01:57 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		seg_exit(void)
{
	ft_putstr_fd("42sh: segmentation fault  ", 2);
	ft_putendl_fd(get_name_prog(NULL), 2);
}

void			safe_exit(int a, char *str)
{
	char	c;

	c = 0;
	get_name_prog(str);
	if (a == SIGINT)
		return ;
	if (a == SIGSEGV)
		seg_exit();
}
