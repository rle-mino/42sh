/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clipboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 16:56:05 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/13 19:46:29 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void		clipboard_to_line(char *first_chars, t_le *le)
{
	char	buffer[1024];
	int		i;

	i = -1;
	while (first_chars[++i])
	{
		if (ft_isprint(first_chars[i]) && !ft_isspace(first_chars[i]))
			add_to_line(le, &(le->line), first_chars[i]);
		else if (ft_isprint(first_chars[i]) && ft_isspace(first_chars[i]))
			add_to_line(le, &(le->line), ' ');
	}
	i = -1;
	ft_bzero(buffer, sizeof(buffer));
	read(0, buffer, 1023);
	while (buffer[++i])
	{
		if (ft_isprint(buffer[i]) && !ft_isspace(buffer[i]))
			add_to_line(le, &(le->line), buffer[i]);
		else if (ft_isprint(buffer[i]) && ft_isspace(buffer[i]))
			add_to_line(le, &(le->line), ' ');
	}
}
