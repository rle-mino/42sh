/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 17:09:47 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 17:56:03 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"

/*
***		Parsing du buffer pour l'edition de ligne standard
*/

void		ctrld_handle(void)
{
	history(FIRST_HIST, NULL);
	history(WRITE_HIST, NULL);
	close(get_fd(-1));
	exit(EXIT_SUCCESS);
}

void		parse_buffer(char *buffer, t_le *le, int mode)
{
	if (ft_isprint(buffer[0]) && buffer[1] == '\0' && le)
		add_to_line(le, &(le->line), buffer[0]);
	else if (ft_is_arrow(buffer) && le)
		move_cursor(le, ft_is_arrow(buffer), &(le->line), mode);
	else if (ft_is_del_or_back(buffer) && le)
		delete_char(le, &(le->line), buffer[0]);
	else if (buffer[0] == 033 && buffer[1] == 033 && buffer[2] == '[' &&
										(buffer[3] == 'D' || buffer[3] == 'C'))
		move_to_word(buffer[3] == 'D' ? LEFT : RIGHT, le);
	else if (buffer[0] == 033 && buffer[1] == 033 && buffer[2] == '[' &&
					(buffer[3] == 'A' || buffer[3] == 'B') && mode != PAIRING)
		move_vertically(buffer[3] == 'A' ? UP : DOWN, le);
	else if (buffer[0] == 033 && buffer[1] == '[' &&
										(buffer[2] == 'H' || buffer[2] == 'F'))
		move_to_extrem(buffer[2] == 'H' ? LEFT : RIGHT, le);
	else if (buffer[0] == 4 && buffer[1] == 0)
		ctrld_handle();
	else if (buffer[0] == '\t' && buffer[1] == 0 && le)
		complete_word(&(le->line), le);
	else if (buffer[0] != '\n' && ft_isprint(buffer[0]) && le)
		clipboard_to_line(buffer, le);
	else if (buffer[0] == 12 && buffer[1] == 0 && buffer[2] == 0 && le)
		ft_builtin_clear();
}

char		*parse_buffer_completion(char *buffer, int *selected, void *poss)
{
	t_word	*word;

	word = poss;
	if (buffer[0] == '\n' || buffer[0] == ' ')
		return (selected_word(word, *selected));
	else if ((buffer[0] == 033 && buffer[1] == '[' && buffer[2] == 'C') ||
															buffer[0] == '\t')
		(*selected)++;
	else if (buffer[0] == 033 && buffer[1] == '[' && buffer[2] == 'D')
		(*selected)--;
	else if (buffer[0] == 033 && buffer[1] == '[' && buffer[2] == 'A')
		*selected -= files_per_lines(word);
	else if (buffer[0] == 033 && buffer[1] == '[' && buffer[2] == 'B')
		*selected += files_per_lines(word);
	else if (ft_isprint(buffer[0]) && buffer[1] == 0)
		return (ft_char_to_string(buffer[0]));
	if (*selected < 0)
		*selected = nb_word(poss) - 1;
	if ((size_t)(*selected) > nb_word(poss) - 1)
		*selected = 0;
	return (NULL);
}
