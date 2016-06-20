/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 12:06:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 11:09:44 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"

/*
***		Gestion complete de l'historique
*/

t_line			*to_line(char *cmd)
{
	int		i;
	t_line	*old_line;
	t_line	*tmp;

	i = -1;
	old_line = ft_memalloc(sizeof(t_line));
	tmp = old_line;
	while (cmd[++i] && i < 300)
	{
		tmp->next = ft_memalloc(sizeof(t_line));
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->c = cmd[i];
	}
	return (old_line);
}

/*
***		lit, si possible, un fichier a la racine de la session
***		et en fait une liste chainee
*/

static t_hist	*read_history(void)
{
	t_hist		*history;
	t_hist		*tmp_hist;
	char		*tmp;
	int			fd;
	int			i;

	fd = get_hist_fd();
	i = 0;
	if (fd == -1)
		return (ft_memalloc(sizeof(t_hist)));
	history = ft_memalloc(sizeof(t_hist));
	tmp_hist = history;
	while (get_next_line(fd, &tmp) == 1 && i++ < 1000)
	{
		tmp_hist->prev = generate_hist(to_line(tmp), tmp_hist, NULL);
		tmp_hist = tmp_hist->prev;
		free(tmp);
	}
	free(tmp);
	close(fd);
	return (history);
}

/*
***		Ecrit dans un ficher a la racine de la session
***		l'integralite de l'historique
*/

static void		write_history(t_hist *hist)
{
	int		fd;
	char	*tmp;
	char	*tmp2;

	fd = get_hist_fd();
	if (fd == -1)
		return ;
	hist = hist->prev;
	while (hist)
	{
		tmp = to_string(get_first_line(hist->old_line), RUP_FOR_HIST);
		tmp2 = tmp;
		tmp = ft_strjoin(tmp, "\n");
		free(tmp2);
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		hist = hist->prev;
	}
}

/*
***		Switchs pour controler l'historique
*/

void			history2(int query, t_line *line, t_hist **history,
														t_line **ori_line)
{
	if (query == FIRST_HIST)
		*history = get_first_hist(*history);
	else if (query == ADD_HIST)
		create_new_hist(history, line);
	else if (query == RES_ORI && (*ori_line = ft_memalloc(sizeof(t_line))))
		(*ori_line)->is_orig = 1;
}

void			*history(int query, t_line *line)
{
	static t_hist		*history = NULL;
	static t_line		*ori_line = NULL;

	if (query == SAVE_LINE)
		ori_line = line;
	else if (query == READ_HIST)
		history = read_history();
	else if (query == NEXT_HIST && history->next)
		history = history->next;
	else if (query == PREV_HIST && history->prev)
		history = history->prev;
	else if (query == WRITE_HIST)
		write_history(history);
	else if (query == GET_HIST)
		return (get_last_hist(history));
	else
		history2(query, line, &history, &ori_line);
	if ((query == NEXT_HIST || query == PREV_HIST) && !(history->old_line))
		return (ori_line);
	if (query == NEXT_HIST || query == PREV_HIST)
		return (cpy_line(get_first_line(history->old_line)));
	return (NULL);
}
