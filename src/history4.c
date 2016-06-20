/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:42:09 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 11:27:51 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static void			delete_request_from_line(t_le *le)
{
	while (le && le->line && le->line->next && le->line->c != ' ')
		delete_char(le, &(le->line), 0);
	delete_char(le, &(le->line), 0);
}

static char			*find_hist(char *to_find, t_hist *hist)
{
	char	*tmp;

	hist = get_first_hist(hist);
	if (hist && hist->prev && to_find && to_find[0] == '!'
										&& hist->prev->old_line)
		return (to_string(hist->prev->old_line, NORMAL));
	while (hist && hist->prev)
	{
		tmp = to_string(hist->old_line, NORMAL);
		if (ft_strstr(tmp, to_find) == tmp)
			return (tmp);
		hist = hist->prev;
		free(tmp);
	}
	return (NULL);
}

static char			*get_elem_to_find(t_line *line)
{
	char	buffer[1024];
	int		i;

	i = 0;
	ft_bzero(buffer, sizeof(buffer));
	if (line)
		line = line->next;
	while (line && line->c != ' ' && i < 1024)
	{
		buffer[i++] = line->c;
		line = line->next;
	}
	return (ft_strdup(buffer));
}

int					add_hist_to_line(t_le *le, char *buffer)
{
	t_hist		*hist;
	char		*tmp;
	char		*to_find;
	int			i;

	i = -1;
	hist = history(GET_HIST, NULL);
	to_find = get_elem_to_find(le->line);
	if (le && to_find && !to_find[0])
	{
		add_to_line(le, &(le->line), ' ');
		return (1);
	}
	if (!(tmp = find_hist(to_find, hist)))
		return (0);
	if (tmp)
		delete_request_from_line(le);
	while (le && tmp && tmp[++i])
		add_to_line(le, &(le->line), tmp[i]);
	if (le && tmp && buffer[0] == ' ')
		add_to_line(le, &(le->line), ' ');
	return (1);
}
