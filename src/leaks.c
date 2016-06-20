/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:28:19 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/19 15:59:25 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

int				end_is_not_in_line(t_le *le, char *end)
{
	char		*tmp;

	tmp = to_string(get_orig_line(le->line), NORMAL);
	if (ft_strcmp(tmp, end) && !le->sig)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
