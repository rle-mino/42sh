/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 19:06:41 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/16 19:30:05 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	malloc_handling(void)
{
	ft_putstr_fd("Allocation failure, exiting.\n", 2);
	exit(EXIT_FAILURE);
}

char	*ft_get_path(t_e *env, char *s)
{
	char		*ret;
	char		**t;
	t_e			*temp;
	int			i;

	ret = NULL;
	temp = env;
	i = 0;
	while (env && temp && ft_start_str("PATH=", temp->str) == 0)
		temp = temp->next;
	if (!temp)
		t = ft_strsplit("/usr/bin:/usr/local/bin:/bin", ':');
	else
		t = ft_go_home(ft_strsplit(temp->str + 5, ':'), env, 0);
	while (t && t[i])
	{
		if (!(ret = ft_sjoinpath(t[i], s)))
			break ;
		if (access(ret, X_OK) != -1)
			break ;
		i++;
	}
	ft_tabdel(t);
	return (ret);
}

t_e		*ft_change_pwd(t_e *env, char *s, int i, char *new)
{
	char		*s2;

	s2 = NULL;
	if (i == -1 || !s)
		return (env);
	s2 = ft_strjoin("setenv OLDPWD ", s);
	ft_strdel(&s);
	s = ft_strjoin(s2, " 1");
	env = call_builtins(s, env, 0);
	ft_strdel(&s2);
	ft_strdel(&s);
	s = getcwd(NULL, 0);
	if (new && new[0] == '/')
		s2 = ft_strjoin("setenv PWD ", new);
	else
		s2 = ft_strjoin("setenv PWD ", s);
	if (s2[ft_strlen(s2) - 1] == '/')
		s2[ft_strlen(s2) - 1] = '\0';
	ft_strdel(&s);
	s = ft_strjoin(s2, " 1");
	env = call_builtins(s, env, 0);
	ft_strdel(&s);
	ft_strdel(&s2);
	return (env);
}

int		ft_print_error(char *s, char *cmd, int i)
{
	struct stat	st;
	char		*s2;

	s2 = NULL;
	if (ft_strequ("built", cmd) && !ft_strequ("cd", s) && !ft_strequ("env", s)
			&& !ft_strequ("setenv", s) && !ft_strequ("unsetenv", s))
		ft_putendl_fd((s2 = ft_strjoin(s, ": no such file or directory")), 2);
	else if (ft_strequ("cd", cmd))
	{
		ft_putstr_fd(cmd, 2);
		if (access(s, F_OK) == -1 || stat(s, &st) == -1)
			ft_putstr_fd(": no such file or directory: ", 2);
		else if (access(s, R_OK) == -1)
			ft_putstr_fd(": permission denied: ", 2);
		else if (!S_ISDIR(st.st_mode))
			ft_putstr_fd(": not a directory: ", 2);
		ft_putendl_fd(s, 2);
	}
	else if (ft_strequ("setenv", cmd) && i < 3)
		ft_putendl_fd("setenv: not enough arguments", 2);
	else if (ft_strequ("setenv", cmd) && i > 4)
		ft_putendl_fd("setenv: too much arguments", 2);
	ft_strdel(&s2);
	return (1);
}
