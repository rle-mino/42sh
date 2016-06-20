/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 15:27:45 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/18 19:28:46 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_e		*call_builtins2(char *s, char **t, t_e *env, int i)
{
	if (env && t && t[0] && ft_strequ("read", t[0]))
		env = ft_read(s, env);
	else if (t && t[0] && ft_strequ("echo", t[0]))
		(ft_strequ("-n", t[1])) ? ft_echo(&t[1], 0) : ft_echo(&t[0], 1);
	else if (env && t && t[0] && ft_strequ("export", t[0]))
		env = ft_setexport(t, env, 0, i);
	else if (env && t && t[0] && ft_strequ("unset", t[0]))
		env->export = ft_unset(t, env->export, i, env);
	else if (env && t && t[0] && back_strchr(t[0], '=') != NULL)
		env->export = ft_export_temp(t, s, env->export, env);
	else if (t && t[0] && ft_strequ("reset", t[0]))
		reset_and_clear();
	else if (t && (ft_strequ("clear", t[0]) || ft_strstr("/clear", t[0])))
		ft_builtin_clear();
	else if (t && t[0] && ft_strequ("exit", t[0]))
	{
		ft_tabdel(t);
		return (env);
	}
	else if (t)
		ft_print_error(t[0], "built", 0);
	ft_tabdel(t);
	return (env);
}

t_e		*call_builtins(char *s, t_e *env, int i)
{
	char	**t;

	t = NULL;
	if (is_empty(s) || !(t = ft_inhib(s, &env)))
		return (env);
	if (env)
		env->status = 0;
	if (t && t[0] && ft_strequ("cd", t[0]))
		env = ft_cd(t, env, 0, getcwd(NULL, 0));
	else if (t && t[0] && ft_strequ("env", t[0]))
		ft_env(t, env);
	else if (t && t[0] && ft_strequ("setenv", t[0]))
		env = ft_setenv(t, env, 0, i);
	else if (t && t[0] && ft_strequ("unsetenv", t[0]))
		env = ft_unsetenv(t, env, i);
	else if (t && t[0] && ft_strequ("history", t[0]))
		ft_history(t);
	else
		return (call_builtins2(s, t, env, i));
	ft_tabdel(t);
	return (env);
}
