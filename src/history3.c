/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 13:17:43 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 11:03:13 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "edit_line.h"

int			dina_hist(t_le *le, char *buffer)
{
	t_line	*actual;
	int		indquote;

	actual = le->line;
	if (buffer[0] != ' ' && buffer[0] != '\n')
		return (-1);
	indquote = 0;
	move_left(le, &(le->line));
	while (le->line->prev && le->line && le->line->c != ' ')
	{
		if (is_a_unescaped_quote(le->line))
			indquote = indquote ^ 1;
		if (le->line->c == '!' && !indquote &&
			((le->line->prev && le->line->prev->c != '!') || !le->line->prev))
		{
			if (!add_hist_to_line(le, buffer))
				break ;
			else
				return (1);
		}
		move_left(le, &le->line);
	}
	while (le->line && le->line != actual)
		move_right(le, &(le->line));
	return (0);
}

t_hist		*get_last_hist(t_hist *hist)
{
	while (hist && hist->prev)
		hist = hist->prev;
	return (hist);
}

int			display_from_first(t_hist *hist, int i)
{
	char	*tmp;

	hist = get_first_hist(hist);
	if (hist && hist->prev)
		hist = hist->prev;
	while (hist && i)
	{
		tmp = to_string(get_first_line(hist->old_line), NORMAL);
		ft_putendl(tmp);
		free(tmp);
		i--;
		hist = hist->prev;
	}
	return (1);
}

int			display_from_last(t_hist *hist, char *arg)
{
	char	*tmp;

	while (hist && hist->next)
	{
		tmp = to_string(get_first_line(hist->old_line), NORMAL);
		if (!arg || ft_strstr(tmp, arg) == tmp)
			ft_putendl(tmp);
		free(tmp);
		hist = hist->next;
	}
	return (1);
}

int			ft_history(char **t)
{
	t_hist	*hist;

	hist = history(GET_HIST, NULL);
	if (t[1] && ft_isdigit(t[1][0]))
		return (display_from_first(hist, ft_atoi(t[1])));
	else
		display_from_last(hist, t[1]);
	return (1);
}
