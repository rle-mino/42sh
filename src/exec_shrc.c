/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shrc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 21:01:29 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 21:08:30 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_e		*exec_cmd_shrc(t_e *e, int fd)
{
	char	*line;

	line = NULL;
	if (!e)
		return (e);
	while (get_next_line(fd, &line) > 0)
	{
		e = ft_exec_cmd(line, e, -1);
		ft_strdel(&line);
	}
	return (e);
}

t_e				*exec_shrc(t_e *e)
{
	int		fd;
	char	*tmp;

	if (!e)
		return (e);
	if (!(tmp = getenv("HOME")))
		tmp = "";
	tmp = ft_strjoin(tmp, "/.42shrc");
	if (!tmp)
		malloc_handling();
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return (e);
	free(tmp);
	return (exec_cmd_shrc(e, fd));
}
