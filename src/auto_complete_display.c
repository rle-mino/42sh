/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_display.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 19:48:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/07 19:27:11 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"

int				files_per_lines(void *word)
{
	t_word				*poss;
	struct winsize		w;
	int					i;
	size_t				max_len;

	poss = word;
	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	max_len = get_max_len(poss);
	i = (w.ws_col - 10) / max_len;
	return (i);
}

static void		display(int selected, t_word *poss, size_t *spaces,
																size_t max_len)
{
	if (selected == 0)
		tputs(tgetstr("so", NULL), 1, ft_putint);
	if (poss)
	{
		ft_putstr_fd(poss->word, get_fd(-1));
		*spaces = ft_strlen(poss->word);
		while ((*spaces)++ < max_len)
			ft_putchar_fd(' ', get_fd(-1));
		if (selected == 0)
			tputs(tgetstr("se", NULL), 1, ft_putint);
	}
}

size_t			get_max_len(void *word)
{
	size_t		max;
	t_word		*words;

	max = 0;
	words = word;
	while (words)
	{
		max = max < ft_strlen(words->word) ? ft_strlen(words->word) : max;
		words = words->next;
	}
	return (max + 1);
}

static void		adjust_len(size_t *actual_len, t_le *le, int *pos_y,
																int max_len)
{
	if (le && *actual_len + max_len > (size_t)le->w_sizex - 10)
	{
		tputs(tgetstr("do", NULL), 1, ft_putint);
		*actual_len = 0;
		(*pos_y)++;
	}
	*actual_len += max_len;
}

void			display_poss(void *list, int *pos_y, int selected, t_le *le)
{
	size_t		spaces;
	size_t		max_len;
	size_t		actual_len;
	t_word		*poss;

	poss = list;
	max_len = get_max_len(poss);
	actual_len = 0;
	while (poss)
	{
		adjust_len(&actual_len, le, pos_y, max_len);
		display(selected, poss, &spaces, max_len);
		ft_putchar_fd(' ', get_fd(-1));
		if (le && *pos_y > le->w_sizey - 2)
		{
			ft_putstr_fd("...", get_fd(-1));
			break ;
		}
		selected--;
		poss = poss->next;
	}
}
