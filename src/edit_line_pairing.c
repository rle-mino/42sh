/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_pairing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 19:04:52 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/09 14:19:38 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
***		gere l'appairage de certains caracteres recursivement
*/

static void			create_first_line(t_le *le, int bsn)
{
	if (!bsn || !le->line)
		le->line = ft_memalloc(sizeof(t_line));
	else
	{
		le->line->next = ft_memalloc(sizeof(t_line));
		le->line->next->prev = le->line;
		le->line = le->line->next;
	}
	le->line->c = bsn ? '\n' : 0;
	le->line->is_orig = 1;
}

static void			prepare_here_doc(t_line **line)
{
	t_line		*tmp;

	tmp = *line;
	if ((*line)->prev)
		*line = (*line)->prev;
	if ((*line)->next)
		tmp = (*line)->next;
	clear_line(tmp);
	(*line)->next = NULL;
}

void				edit_line_pairing(t_le *le, char *prompt)
{
	char	buffer[6];

	le->pos_x = ft_strlen(prompt);
	ft_putstr_fd(prompt, get_fd(-1));
	create_first_line(le, 1);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le, PAIRING);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if ((le->prompt = missing_pair(get_first_line(le->line),
									ft_memalloc(sizeof(int) * 2))))
		edit_line_pairing(le, le->prompt);
}

t_line				*edit_line_heredoc(t_le *le, char *end, int bsn)
{
	char			buffer[6];

	ft_putstr_fd("heredoc> ", get_fd(-1));
	le->pos_x = ft_strlen("heredoc> ");
	create_first_line(le, bsn);
	bsn = !bsn ? 1 : bsn;
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le, PAIRING);
		if ((buffer[0] == '\n' && buffer[1] == 0) || le->sig)
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if (end_is_not_in_line(le, end))
		edit_line_heredoc(le, end, 1);
	else if (!le->sig && (le->line = get_orig_line(le->line)))
		prepare_here_doc(&(le->line));
	return (get_first_line(le->line));
}
