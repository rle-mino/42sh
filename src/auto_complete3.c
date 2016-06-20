/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 17:37:23 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 17:45:25 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "arbre.h"
#include "minishell.h"

void		error_too_many_poss(t_le *le, int pos_x)
{
	while (le && le->line && le->line->next)
		move_right(le, &(le->line));
	tputs(tgetstr("do", NULL), 1, ft_putint);
	ft_putstr_fd("Too many possibilities", get_fd(-1));
	tputs(tgetstr("do", NULL), 1, ft_putint);
	tputs(tgetstr("up", NULL), 1, ft_putint);
	tputs(tgetstr("up", NULL), 1, ft_putint);
	while (le && pos_x++ < le->pos_x)
		tputs(tgetstr("nd", NULL), 1, ft_putint);
}

int			too_many_or_less_poss(void *word, t_le *le)
{
	t_word				*poss;
	size_t				max_len;
	struct winsize		w;
	int					words_per_lines;
	int					pos_x;

	poss = word;
	pos_x = 0;
	max_len = get_max_len(word);
	ioctl(0, TIOCGWINSZ, &w);
	words_per_lines = (w.ws_col - 10) / max_len;
	if (w.ws_row - 2 < nb_word(poss) / words_per_lines || nb_word(poss) < 2)
	{
		if (w.ws_row - 2 < nb_word(poss) / words_per_lines)
			error_too_many_poss(le, pos_x);
		return (1);
	}
	return (0);
}

char		*delete_useless_char(char *a, char *b)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (a && b && a[i] == b[i])
		i++;
	if (a)
		new = ft_strdup(a + i);
	return (new);
}

void		free_autocomplete(t_arbre *tmp, char *buffer, char **path_and_word)
{
	free_arbre(&tmp);
	free(buffer);
	free(path_and_word[0]);
	free(path_and_word[1]);
	free(path_and_word);
}
