/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 12:15:19 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/19 23:28:37 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_go_home2(char *s, char *s2)
{
	char	*tmp;

	tmp = NULL;
	if (s[0] && s[1])
		tmp = ft_strjoin(s2, s + 1);
	ft_strdel(&s);
	s = go_homu(tmp, s2);
	return (s);
}

char	*cmd_redirless3(char *ret, char *s, int i)
{
	char	*tmp;

	tmp = ft_strjoin(ret, s + i + 4 + fuck_la_norme(s + i + 4));
	ft_strdel(&ret);
	return (tmp);
}

int		*ret_redir_fd(int *redir)
{
	redir[0] = 1;
	redir[1] = 2;
	return (redir);
}

int		*ret_special_fd(int *file, char *s, int i)
{
	if (!s[i] && i == 0)
		file[0] = 2;
	else if (!s[i])
		file[0] = ft_atoi(s);
	else
	{
		if (ft_strequ(s + i, "-"))
			file[0] = open("/dev/null", O_RDWR);
		else if (file[1] == 0)
			file[0] = open(s, O_RDONLY);
		else if (file[1] == 1)
			file[0] = open(s, O_CREAT | O_RDWR | O_TRUNC, 0755);
		else
			file[0] = open(s, O_CREAT | O_RDWR | O_APPEND, 0755);
	}
	return (file);
}

t_e		*ft_exec_cmd2(t_e *env, char *cmd, char **arg, char *s)
{
	if (ft_exit(cmd, s, arg, env) == 1)
		ft_clean_exit(0, s, arg, env);
	else if (double_red(cmd, '&') == 1 ||
			double_red(cmd, '|') == 1)
		env = ft_logical_operator(cmd, env, count_op(cmd));
	else if (back_strchr(cmd, '|') != NULL)
		env = ft_pipe(env, cmd, -1, count_char(cmd, '|'));
	else if (back_strchr(cmd, '<') != NULL
			|| back_strchr(cmd, '>') != NULL)
		env = ft_redir_loop(env, cmd);
	else if (ft_ispath(cmd) == 0 && !is_empty(cmd))
		env = ft_exec(env, cmd, switch_env(env), NULL);
	else if (ft_ispath(cmd) == 1)
		env = ft_exec_path(env, cmd, NULL, NULL);
	else if (ft_ispath(cmd) == 2)
		env = call_builtins(cmd, env, 1);
	return (env);
}
