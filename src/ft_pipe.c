/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 14:51:09 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/17 21:08:20 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

struct sigaction sigchld_action = {
	.sa_handler = SIG_DFL, .sa_flags = SA_NOCLDWAIT
};

int		double_red(char *s, char c)
{
	int		i;

	i = -1;
	while (s && s[++i])
		if (s[i] == c && s[i + 1] && s[i + 1] == c)
			return (1);
	return (-1);
}

t_e		*pipe_2(t_e *env, char *s, int i, int n)
{
	pid_t	pid;
	int		status;
	int		pdes[2];

	pipe(pdes);
	pid = fork();
	if (pid)
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
	else
	{
		dup2(pdes[1], fd_loop(s));
		close(pdes[0]);
		env = ft_exec_pipe(final_flash(s), env);
		exit(0);
	}
	dup2(pdes[0], 0);
	close(pdes[1]);
	if (i + 1 == n)
	{
		env = ft_exec_cmd(final_flash(no_char(s, '|')), env, -1);
		dup2(1, 0);
	}
	close(pdes[0]);
	close(pdes[1]);
	return (env);
}

char	*wait_pipe(char *tmp, char *new, char *f)
{
	while (1)
	{
		print_pipe(new, ft_strdup(""), -1, 0);
		if (get_next_line(1, &tmp) >= 0 && tmp && ft_strequ("", tmp) != 1)
		{
			f = new;
			new = ft_strjoin(new, tmp);
			if (tmp[0] == '|' || double_red(tmp, '|') == 1
					|| (tmp[0] == '&' && f[ft_strlen(f)] != '|'))
			{
				ft_strdel(&f);
				ft_strdel(&tmp);
				ft_strdel(&new);
				return (NULL);
			}
			ft_strdel(&f);
			if (tmp[ft_strlen(tmp) - 1] != '|'
					&& tmp[ft_strlen(tmp) - 1] != '&')
				break ;
		}
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	return (new);
}

t_e		*ft_pipe(t_e *env, char *s, int i, int j)
{
	char	*tmp;
	char	*f;

	tmp = s;
	if (ft_pipe_parse_error(s))
		return (ret_env_err(env, 127));
	if (ft_strlen(s) - 1 > 0 &&
	(s[ft_strlen(s) - 1] == '|' || s[ft_strlen(s) - 1] == '&'))
		s = wait_pipe(NULL, ft_strdup(s), NULL);
	f = s;
	if (!s)
	{
		ft_putendl_fd("42sh: parse error near `|'", 2);
		return (ret_env_err(env, 127));
	}
	while (++i != j)
	{
		env = pipe_2(env, s, i, j);
		s = no_char(s, '|');
	}
	if (!ft_strequ(tmp, f))
		ft_strdel(&f);
	return (env);
}

t_e		*ft_exec_pipe(char *str, t_e *env)
{
	char	*s;

	if (str && env)
	{
		s = ft_str_trunc(str, '|');
		env = ft_exec_cmd(s, env, -1);
		env->status = get_ret(-12);
		ft_strdel(&s);
	}
	return (env);
}
