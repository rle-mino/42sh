/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 21:09:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 11:20:26 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"

/*
***		Gestion de l'historique
*/

static int	invalid_line(t_line *line)
{
	int		valid;

	valid = 0;
	line = line->next;
	while (line)
	{
		if (line->c != ' ' && line->c != '\0')
			valid = 1;
		if (line->c == '\n')
			return (1);
		line = line->next;
	}
	return (valid ? 0 : 1);
}

t_hist		*generate_hist(t_line *cmd, t_hist *next, t_hist *prev)
{
	t_hist		*new;

	new = ft_memalloc(sizeof(t_hist));
	new->old_line = cut_line_for_hist(cmd);
	new->next = next;
	new->prev = prev;
	return (new);
}

t_hist		*get_first_hist(t_hist *hist)
{
	t_hist	*a;

	a = hist;
	while (a && a->next)
		a = a->next;
	return (a);
}

void		create_new_hist(t_hist **history, t_line *line)
{
	if (linelen(line) > 1 && !invalid_line(line))
	{
		(*history)->prev = generate_hist(line, *history, (*history)->prev);
		*history = (*history)->prev;
		if ((*history)->prev && (*history)->prev->prev)
			(*history)->prev->next = *history;
	}
	else
		clear_line(line);
}

int			get_hist_fd(void)
{
	char		*tmp;
	int			fd;

	if (!(tmp = getenv("HOME")))
		tmp = "";
	tmp = ft_strjoin(tmp, "/.history");
	if ((fd = open(tmp, O_RDWR, 644)) == -1)
		ft_putstr_fd("history unavailable\n", 2);
	free(tmp);
	return (fd);
}
