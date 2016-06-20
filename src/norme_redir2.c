/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:22:51 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/19 20:02:57 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		count_red_help(char *s)
{
	int		i;
	int		n;
	bool	c;

	i = -1;
	n = 0;
	c = false;
	while (s[++i])
	{
		if (s[i] == '>' && i > 0 && s[i - 1] != '>'
				&& !ft_backslash_check(s, i))
		{
			if (!c)
				c = true;
			else
				n++;
		}
		else if (!ft_isalnum(s[i]) && !ft_isspace(s[i])
				&& !ft_backslash_check(s, i))
			break ;
	}
	return (n);
}

char	*ret_next(char *s, int i)
{
	int		n;

	n = 0;
	while (i >= 0)
	{
		while (s[n] && s[n] == '>' && !ft_backslash_check(s, i))
			n++;
		while (s[n] && (s[n] != '>' || (s[n] == '>'
						&& ft_backslash_check(s, n))))
			n++;
		i--;
	}
	return (s + n);
}

t_e		*ft_redir_loop(t_e *e, char *s)
{
	pid_t	pid;
	int		status;
	int		err;
	int		std_copy;

	status = 0;
	if ((pid = fork()))
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
	else
	{
		std_copy = dup(0);
		if ((err = loop_redir(s, std_copy)))
			redir_error(err);
		ft_exec_cmd(s, e, -1);
		exit(0);
	}
	e = ret_env_err(e, status);
	return (e);
}

/*
***t_e		*ft_redir_loop(t_e *e, char *s)
***{
***	int		i;
***	int		n;
***	char	*tmp;
***	char	*cmd;
***	char	*no_redir;
***	if (!ft_strchr(s, '>'))
***		return (ft_redir(e, s, NULL));
***	i = 0;
***	n = count_red_help(s);
***	tmp = s;
***	while (i <= n)
***	{
***		no_redir = cmd_redirless(s, -1);
***		tmp = ret_next(s, i);
***		cmd = ft_strlink(no_redir, tmp, ' ');
***		e = ft_redir(e, cmd, NULL);
***		ft_strdel(&cmd);
***		if (e && e->status != 0)
***			break ;
***		i++;
***	}
***	return (e);
***}
*/
