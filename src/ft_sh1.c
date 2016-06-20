/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:10:47 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/20 09:11:31 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "edit_line.h"

int		ft_builtins(char *s)
{
	int		i;
	char	*s2;

	i = 0;
	while (s && s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	s2 = s + i;
	if (ft_start_str("cd", s2) || ft_start_str("env", s2) ||
			ft_start_str("setenv", s2) || ft_start_str("unsetenv", s2)
			|| ft_start_str("exit", s2) || ft_start_str("echo", s2)
			|| ft_start_str("export", s2) || ft_start_str("unset", s2)
			|| ft_start_str("history", s2) || back_strchr(s, '=')
			|| ft_start_str("read", s) || ft_start_str("reset", s2)
			|| ft_start_str("clear", s2) || ft_strstr("/clear", s2))
		return (1);
	return (0);
}

int		ft_ispath(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	if (ft_builtins(s) == 1)
		return (2);
	while (s && s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s && s[i] && (s[i] != ' ' && s[i] != '\t'))
	{
		if (s[i] == '/' && !ft_backslash_check(s, i))
			return (1);
		i++;
	}
	return (0);
}

t_e		*ft_exec_path(t_e *env, char *s, char **t, char *tmp)
{
	char	**e;
	pid_t	pid;

	e = switch_env(env);
	t = ft_inhib(s, &env);
	if (env && (pid = fork()))
	{
		waitpid(pid, &(env->status), WUNTRACED | WCONTINUED);
		if (env->status == SIGSEGV)
			safe_exit(env->status, t[0]);
	}
	else if (env)
	{
		if (access(t[0], X_OK) == -1 && access(t[0], F_OK) == 0)
			quit_error_fd((tmp = ft_strjoin(t[0], ": permission denied")), 2);
		else if (access(t[0], F_OK) == -1)
			quit_error_fd((tmp =
				ft_strjoin(t[0], ": no such file or directory")), 2);
		else if (execve(t[0], t, e) == -1)
			quit_error_fd((tmp = ft_strjoin(t[0], ": exec format error")), 2);
	}
	free_exec(tmp, t, NULL, e);
	return (env ? ret_env_err(env, env->status) : NULL);
}

t_e		*ft_exec(t_e *env, char *s, char **arg, char *tmp)
{
	char	*s2;
	char	**t;
	pid_t	pid;

	s2 = NULL;
	t = ft_inhib(s, &env);
	if (env && (pid = fork()))
		waitpid(pid, &(env->status), WUNTRACED | WCONTINUED);
	else if (env && arg && t && t[0])
	{
		if (!(s2 = ft_get_path(env, t[0])))
			quit_error_fd("42sh: command not found", 2);
		if (access(s2, X_OK) == -1 && access(s2, F_OK) == 0)
			quit_error_fd((tmp = ft_strjoin(t[0], ": permission denied")), 2);
		else if (access(s2, F_OK) == -1)
			quit_error_fd((tmp = ft_strjoin(t[0], ": command not found")), 2);
		else if (execve(s2, t, arg) == -1)
			quit_error_fd((tmp = ft_strjoin(t[0], ": command not found")), 2);
	}
	else if (env)
		exit(EXIT_SUCCESS);
	free_exec(tmp, arg, s2, t);
	return (env ? ret_env_err(env, env->status) : NULL);
}

int		main(void)
{
	char	*s;
	t_e		*env;
	t_line	*inp;
	t_le	*le;

	le = prepare_term();
	env = ft_init_env();
	history(READ_HIST, NULL);
	while (1)
	{
		if (!env)
			return (env_err());
		inp = start_edit_line(le, env);
		reset_term();
		s = to_string(inp, NORMAL);
		s = ft_glob(s);
		if (s && !ft_strequ("", s))
			env = ft_exec_cmd(s, env, -1);
		init_term();
		history(FIRST_HIST, NULL);
		history(ADD_HIST, inp);
	}
	ft_clean_exit(0, NULL, NULL, env);
	return (0);
}
