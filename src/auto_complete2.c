/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:53:46 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/08 15:50:19 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"

static void		filt_poss(t_word **word, char *str)
{
	t_word	*tmp;
	t_word	*tmp2;

	while (*word && ft_strstr((*word)->word, str) != (*word)->word && str[0])
	{
		tmp = *word;
		*word = (*word)->next;
		free(tmp->word);
		free(tmp);
	}
	tmp2 = *word;
	while (tmp2)
	{
		if (tmp2->next && ft_strstr(tmp2->next->word, str) != tmp2->next->word
																	&& str[0])
		{
			tmp = tmp2->next;
			tmp2->next = tmp2->next->next;
			free(tmp->word);
			free(tmp);
		}
		else
			tmp2 = tmp2->next;
	}
}

char			*selected_word(void *data, int selected)
{
	t_word		*word;

	word = data;
	while (word && selected)
	{
		word = word->next;
		selected--;
	}
	return (word ? word->word : NULL);
}

static void		update_completion(t_le *le, int selected, t_word *poss,
																	t_line *ori)
{
	int		pos_x;
	int		pos_y;

	pos_x = 0;
	pos_y = 0;
	tputs(tgetstr("do", NULL), 1, ft_putint);
	display_poss(poss, &pos_y, selected, le);
	tputs(tgetstr("do", NULL), 1, ft_putint);
	tputs(tgetstr("up", NULL), 1, ft_putint);
	while (pos_y--)
		tputs(tgetstr("up", NULL), 1, ft_putint);
	tputs(tgetstr("up", NULL), 1, ft_putint);
	while (pos_x++ < le->pos_x)
		tputs(tgetstr("nd", NULL), 1, ft_putint);
	while (le->line && le->line->prev && le->line != ori)
		move_left(le, &(le->line));
}

static char		*loop_completion(t_word *poss, t_le *le, t_line *ori)
{
	char	buffer[6];
	int		selected;
	char	*to_add;

	selected = 0;
	to_add = NULL;
	le->sig = 0;
	update_completion(le, selected, poss, ori);
	while (1)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		if (le->sig || ((buffer[0] == 033 || buffer[0] == 127) &&
																buffer[1] == 0))
			break ;
		else if ((to_add = parse_buffer_completion(buffer, &selected, poss)))
			break ;
		update_completion(le, selected, poss, ori);
		if (too_many_or_less_poss(poss, le))
			return (NULL);
	}
	le->sig = 0;
	return (to_add);
}

void			advanced_completion(t_le *le, char **path_and_word)
{
	t_word		*poss;
	t_line		*ori;
	t_line		*line;
	char		*to_add;

	poss = get_files(path_and_word[0]);
	filt_poss(&poss, path_and_word[1]);
	ori = le->line;
	if (too_many_or_less_poss(poss, le))
	{
		while (le->line->prev && le->line != ori)
			move_left(le, &(le->line));
		clear_words(poss);
		return ;
	}
	while (le->line && le->line->next)
		move_right(le, &(le->line));
	line = le->line;
	to_add = loop_completion(poss, le, line);
	to_add = delete_useless_char(to_add, path_and_word[1]);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	add_word_to_line(to_add, le);
	free(to_add);
	clear_words(poss);
}
