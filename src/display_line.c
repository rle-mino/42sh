/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 18:16:44 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 17:52:38 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
***		Changement visuel de l'edition de ligne
*/

static void		replace_cursor(int i, t_le *le)
{
	if (le && le->pos_x == le->w_sizex)
	{
		tputs(tgetstr("do", NULL), 1, ft_putint);
		le->pos_x = 0;
	}
	while (i > 0)
	{
		if (le && le->pos_x == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			while (le && le->pos_x++ < le->w_sizex - 1)
				tputs(tgetstr("nd", NULL), 1, ft_putint);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putint);
		i--;
		if (le)
			le->pos_x--;
	}
}

void			add_to_line_display(t_le *le, t_line **line)
{
	if (le)
		le->pos_x++;
	if (*line)
		ft_putchar_fd((*line)->c, get_fd(-1));
	if (le && le->pos_x >= le->w_sizex)
	{
		le->pos_x = 0;
		le->pos_y++;
		tputs(tgetstr("do", NULL), 1, ft_putint);
	}
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	if (*line)
		redisplay_line((*line)->next, le);
}

void			delete_char_display(t_line **line, t_le *le)
{
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	redisplay_line(*line, le);
}

int				redisplay_line_index(t_line *line, t_le *le)
{
	t_line	*tmp;
	char	area[1024];
	int		i;
	int		x;

	i = 0;
	x = 4;
	tmp = line;
	while (tmp && i < 1024)
	{
		if (le && x == le->w_sizex)
			x = 0;
		area[i] = tmp->c;
		tmp = tmp->next;
		i++;
		x++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
	return (x);
}

void			redisplay_line(t_line *line, t_le *le)
{
	t_line	*tmp;
	char	area[1024];
	int		i;

	i = 0;
	tmp = line;
	while (tmp && i < 1024)
	{
		area[i] = tmp->c;
		if (le && le->pos_x == (le->w_sizex))
			le->pos_x = 0;
		le->pos_x++;
		tmp = tmp->next;
		i++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
	replace_cursor(i, le);
}
