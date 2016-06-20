/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_detect_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 19:57:51 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 10:35:36 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		detect_fd_redir_in(char *redir, int *i, int *fd, int *heredoc)
{
	if (ft_isdigit(redir[*i]))
	{
		*fd = redir[*i] - '0';
		redir[(*i)++] = ' ';
	}
	if (redir[*i] == '<' && redir[*i + 1] == '<')
	{
		*heredoc = 1;
		redir[(*i)++] = ' ';
		redir[(*i)++] = ' ';
	}
	else
		redir[(*i)++] = ' ';
}

int				detect_redir_in(char *redir, int save_fd)
{
	int		i;
	int		fd;
	int		heredoc;
	char	*to_redir;

	i = 0;
	fd = 0;
	heredoc = 0;
	to_redir = NULL;
	detect_fd_redir_in(redir, &i, &fd, &heredoc);
	if (redir[i] == '&')
		return (AMBIGUOUS_REDIR);
	while (redir[i] && ft_isspace(redir[i]))
		i++;
	if (!redir[i])
		return (NEED_FILENAME);
	to_redir = get_name_of_redir(redir, i);
	return (redirection_in(fd, to_redir, heredoc, save_fd));
}
