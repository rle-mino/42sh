/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 21:14:55 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 23:03:29 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_next_redir(char *str, int i)
{
	while (str[i] && !is_a_redir(str[i]))
		i++;
	if (str[i] && ft_isdigit(str[i - 1]))
		i--;
	return (i);
}

static void		close_redir(char *redir)
{
	int		i;

	i = 0;
	if (ft_isdigit(redir[0]))
		close(redir[0] - '0');
	else
		close(1);
	while (redir[i] && redir[i] != '-')
	{
		redir[i++] = ' ';
	}
	redir[i] = ' ';
}

char			*get_name_of_redir(char *redir, int i)
{
	int		j;
	int		quotes;
	char	*to_redir;

	j = 0;
	quotes = 0;
	to_redir = ft_memalloc(1024);
	if (redir[i] == '\'' || redir[i] == '\"')
	{
		quotes = redir[i];
		to_redir[j++] = redir[i];
		redir[i++] = ' ';
	}
	while (redir[i] &&
				(quotes || (!ft_isspace(redir[i]) && !is_a_redir(redir[i]))))
	{
		to_redir[j++] = redir[i];
		redir[i] = ' ';
		if (redir[i++] == quotes)
			break ;
	}
	return (to_redir);
}

int				loop_redir(char *str, int save_fd)
{
	int		i;
	int		err;

	i = 0;
	err = 1;
	while (str[i])
	{
		i = get_next_redir(str, i);
		if (match("[0-9][<>]&-*", str + i) || match("[<>]&-*", str + i))
			close_redir(str + i);
		else if ((str[i] == '>' || str[i + 1] == '>') &&
										(err = word_before_redir(str, i)))
			err = detect_redir_out(str + i);
		else if ((str[i] == '<' || str[i + 1] == '<') &&
											(err = word_before_redir(str, i)))
		{
			err = detect_redir_in(str + i, save_fd);
		}
		if (err != 1)
			return (err);
	}
	return (0);
}
