/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir_inout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 14:25:50 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 10:49:10 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		redir_heredoc(char *content, int fd, int save_fd)
{
	int			tmpfd;
	t_line		*heredoc_data;
	t_le		*le;
	static int	mdr = 0;

	if (mdr > 0)
		dup2(save_fd, 0);
	le = prepare_term();
	mdr++;
	if ((tmpfd = open("/tmp/.heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
		return (OPEN_ERROR);
	heredoc_data = edit_line_heredoc(le, content, 0);
	content = to_string(heredoc_data, NORMAL);
	clear_line(heredoc_data);
	write(tmpfd, content, ft_strlen(content));
	close(tmpfd);
	free(content);
	if ((tmpfd = open("/tmp/.heredoc", O_RDWR)) == -1)
		return (0);
	dup2(tmpfd, fd);
	close(tmpfd);
	reset_term();
	return (1);
}

int				redirection_in(int fd, char *content, int heredoc, int save_fd)
{
	int			filefd;
	struct stat	stat_file;

	if (content && !heredoc)
		content = clear_str(content);
	filefd = -1;
	if (heredoc)
		return (redir_heredoc(content, fd, save_fd));
	else
	{
		if (lstat(content, &stat_file))
			return (IS_NOT_VALID);
		if ((filefd = open(content, O_RDONLY)) == -1)
			return (OPEN_ERROR);
		dup2(filefd, fd);
		close(filefd);
	}
	return (1);
}

int				redirection_out(int fd, char *filename, int append)
{
	int			filefd;
	struct stat	stat_file;

	if (filename)
		filename = clear_str(filename);
	filefd = -1;
	if (fd > 0 && (!lstat(filename, &stat_file) &&
		(S_ISDIR(stat_file.st_mode) || S_ISLNK(stat_file.st_mode))))
		return (IS_NOT_VALID);
	if (fd > 0 && !append &&
			(filefd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
		return (OPEN_ERROR);
	else if (fd > 0 &&
			(filefd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
		return (OPEN_ERROR);
	if (fd == 3)
	{
		dup2(filefd, STDOUT_FILENO);
		dup2(filefd, STDERR_FILENO);
	}
	else if (fd >= 0 && fd <= 2)
		dup2(filefd, fd);
	else
		dup2(filefd, STDOUT_FILENO);
	return (1);
}
