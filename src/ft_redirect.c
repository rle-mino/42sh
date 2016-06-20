/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 15:43:14 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/18 19:29:23 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*filename2(char *s, char c)
{
	char	*name;

	name = no_char(s, c);
	if (double_red(s, c) == 1)
		name = no_char(name, c);
	return (name);
}

char	*get_filename(char **t, int i)
{
	char	*name;

	name = NULL;
	while (t && t[++i])
	{
		if (((!ft_strequ(t[i], ">") || !ft_strequ(t[i], ">>"))
					&& back_strchr(t[i], '>') != NULL
					&& t[i][ft_strlen(t[i]) - 1] != '>') ||
				(i > 0 && (ft_strequ(t[i - 1], ">") || ft_strequ(t[i - 1], ">>")
						|| t[i - 1][ft_strlen(t[i - 1]) - 1] == '>')))
		{
			name = filename2(t[i], '>');
			break ;
		}
		else if (((!ft_strequ(t[i], "<") || !ft_strequ(t[i], "<<"))
					&& back_strchr(t[i], '<') != NULL
					&& t[i][ft_strlen(t[i]) - 1] != '<') ||
				(i > 0 && (ft_strequ(t[i - 1], "<") || ft_strequ(t[i - 1], "<<")
						|| t[i - 1][ft_strlen(t[i - 1]) - 1] == '<')))
		{
			name = filename2(t[i], '<');
			break ;
		}
	}
	return (ft_strtrim(name));
}

int		ft_open_redir(t_e *env, char *s, int fd, char **t)
{
	char	*name;

	if ((double_red(s, '<') == 1) || ft_strchr(s, '&') != NULL)
		return (-2);
	t = ft_inhib(s, &env);
	name = get_filename(t, -1);
	if (double_red(s, '>') == 1)
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0755);
	else if (back_strchr(s, '>') != NULL)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0755);
	else
		fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		if (!name)
			ft_putendl_fd("42sh: parse error near `\\n'", 2);
		else
		{
			ft_putstr_fd("42sh: error with the redirected file: ", 2);
			ft_putendl_fd(name, 2);
		}
	}
	ft_tabdel(t);
	ft_strdel(&name);
	return (fd);
}

t_e		*ft_redir2(t_e *env, char *s, char *no_redir, char *arg)
{
	char	**t;
	int		pdes[2];
	int		status;
	pid_t	pid;

	t = ft_inhib(s, &env);
	pipe(pdes);
	pid = fork();
	if (pid)
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
	else
	{
		arg = print_llredir(get_filename(t, -1), NULL);
		dup2(pdes[1], 1);
		close(pdes[0]);
		ft_putstr(arg);
		ft_strdel(&arg);
		exit(0);
	}
	dup2(pdes[0], 0);
	close(pdes[1]);
	env = ft_exec_cmd(no_redir, env, -1);
	dup2(1, 0);
	return (clean_red(no_redir, t, env));
}

t_e		*ft_redir(t_e *env, char *s, char *no_redir)
{
	int		status;
	int		fd;
	pid_t	pid;
	int		*redir;

	if ((fd = ft_open_redir(env, s, 0, NULL)) < 0 && ft_strchr(s, '&') == NULL)
		return (norme_got_me(env, s, fd, no_redir));
	if (!(redir = get_redir_fd(s, fd, 0, (int*)malloc(sizeof(int) * 2))))
	{
		if (fd > 0)
			close(fd);
		return (ret_err_redir(ret_env_err(env, 127)));
	}
	if ((pid = fork()))
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
	else
	{
		if (!no_redir)
			no_redir = cmd_redirless(s, -1);
		dup2(redir[0], redir[1]);
		env = ft_exec_cmd(no_redir, env, -1);
		exit(0);
	}
	env = ret_env_err(env, status);
	return (close_red(no_redir, redir, fd, env));
}
