/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/27 17:44:13 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/18 19:29:00 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		*redir_fd_plus(int *redir)
{
	free(redir);
	return (NULL);
}

int		*get_redir_fd(char *s, int fd, int i, int *redir)
{
	if (fd >= 0)
		redir[0] = fd;
	redir[1] = 1;
	if ((back_strchr(s, '<') != NULL && back_strchr(s, '>') == NULL)
			|| ft_strstr(s, "0>") != NULL)
		redir[1] = 0;
	if (ft_strstr(s, "2>") != NULL)
		redir[1] = 2;
	else if (ft_strstr(s, ">") != NULL && ft_strstr(s, "0>") == NULL
			&& ft_strstr(s, "<") != NULL)
		redir[1] = 1;
	if (fd < 0)
	{
		while (s[i] && s[i] != '&')
			i++;
		if (s[i] && s[i] == '&' && (!s[i + 1] || ft_isspace(s[i + 1])))
			return (ret_redir_fd(redir));
		if (i == 0 || (s[i - 1] != '>' && s[i - 1] != '<'))
			return (redir_fd_plus(redir));
		redir = get_special_fd(ft_strtrim(s + i + 1), redir);
		if (redir[0] < 0)
			return (redir_fd_plus(redir));
	}
	return (redir);
}

void	ft_close_red(int *redir, int fd)
{
	if (redir[0] == fd)
		close(fd);
	else
		dup2(2, 2);
	free(redir);
	redir = NULL;
}

char	*cmd_redirless(char *s, int i)
{
	char	*no_redir;
	char	*tmp;

	if (ft_strstr(s, "2>") != NULL || ft_strstr(s, "1>") != NULL
			|| ft_strstr(s, "0>") != NULL)
	{
		while (s[++i])
			if (i > 0 && s[i + 1] && s[i] >= '0'
					&& s[i] <= '2' && (s[i + 1] == '>' || s[i + 1] == '<'))
				break ;
		no_redir = ft_strndup(s, i - 1);
		if (s[i + 2] && s[i + 2] == '&')
			no_redir = cmd_redirless3(no_redir, s, i);
	}
	else if (ft_strstr(s, ">&"))
	{
		while (s[++i])
			if (s[i] == '>' && s[i + 1] == '&')
				break ;
		tmp = ft_strndup(s, i - 1);
		no_redir = ft_strjoin(tmp, s + i + 2 + fuck_la_norme(s + i + 2));
		ft_strdel(&tmp);
	}
	no_redir = cmd_redirless2(s);
	return (no_redir);
}

int		ft_err_red(t_e *env, char *s, int i)
{
	char	**t;

	if (ft_strstr(s, "2>") == NULL && ft_strstr(s, "1>") == NULL
			&& ft_strstr(s, "0>") == NULL && ft_strchr(s, '&') == NULL)
		return (1);
	t = ft_inhib(s, &env);
	while (t[++i])
	{
		if (ft_strchr(t[i], '&') != NULL
				&& (clear_pipe(t, i) == -1 && check_r(t[i]) == -1))
			return (central_fiction(t));
	}
	return (ret_ok(t));
}
