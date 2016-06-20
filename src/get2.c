/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:02:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 13:57:50 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_name_prog(char *str)
{
	static char		*ret = NULL;

	if (str)
		ret = str;
	return (ret);
}

t_e			*get_t_env(t_e *e)
{
	static t_e	*ori_e = NULL;

	if (!ori_e)
		ori_e = e;
	return (ori_e);
}

t_le		*get_t_le(t_le *le)
{
	static t_le	*ori_le = NULL;

	if (!ori_le)
		ori_le = le;
	return (ori_le);
}

t_line		*get_orig_line(t_line *line)
{
	while (line && line->is_orig == 0)
		line = line->prev;
	return (line ? line->next : line);
}
