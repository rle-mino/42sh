/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 10:59:54 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/20 13:33:04 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_get_oldpwd(char *s, t_e *env)
{
	t_e			*temp;

	temp = env;
	while (temp && ft_start_str("OLDPWD=", temp->str) == 0)
		temp = temp->next;
	if (!temp || (s && !ft_strequ(s, "-")))
		return (s);
	ft_strdel(&s);
	s = ft_strdup(temp->str + 7);
	ft_putendl_fd(s, 1);
	return (s);
}

int		ft_exit(char *s, char *cmd, char **arg, t_e *env)
{
	int			i;
	char		**t;

	t = NULL;
	i = 0;
	t = ft_cmdsplit(s);
	if (t && ft_strequ("exit", t[0]))
	{
		i = 1;
		if (t && t[0] && t[1] && t[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			i = 0;
		}
		else if (t[1])
		{
			i = ft_atoi(t[1]);
			ft_tabdel(t);
			t = NULL;
			ft_clean_exit(i, cmd, arg, env);
		}
	}
	if (t)
		ft_tabdel(t);
	return (i);
}

void	print_temp_env(char **t, t_e *env)
{
	int			i;
	t_e			*temp;

	temp = env;
	while (temp)
	{
		t = choose_your_print(t, temp->str);
		temp = temp->next;
	}
	i = 1;
	while (t && t[i])
	{
		if (ft_strchr(t[i], '=') != NULL)
			ft_putendl_fd(t[i], 1);
		i++;
	}
}

void	ft_env_args(char **t, t_e *env)
{
	int			check;
	int			i;
	t_e			*tmp;

	tmp = NULL;
	i = 0;
	check = 1;
	while (t && t[++i])
	{
		if (back_strchr(t[i], '=') != NULL || ft_strequ("env", t[i]))
			check++;
	}
	if (i == check)
		print_temp_env(t, env);
	else
	{
		i = 1;
		while (t[i] && back_strchr(t[i], '=') != NULL)
			i++;
		tmp = ft_gettmp(env, t);
		if (!tmp)
			tmp = ft_add_e(tmp, "test");
		tmp = exec_env_arg(&t[i], tmp);
	}
	ft_deltmp(tmp);
}

t_e		*ft_exec_cmd(char *s, t_e *env, int i)
{
	char	**arg;
	int		ctrl;
	char	*tmp;

	tmp = ft_strdup(s);
	ctrl = 0;
	if (env && s && back_strchr_no_quote(s, '`') != NULL)
		s = ft_replace_back_quote(s, env);
	if (!s || !env || !(arg = ft_backsplit(s, ';')))
		return (env);
	if ((ctrl = is_script(arg)) > 0)
	{
		ft_tabdel(arg);
		arg = ft_backsplit(tmp, ';');
		free(tmp);
		return (do_shell_script_and_follow(env, arg, ctrl));
	}
	free(tmp);
	if (arg && is_cdt(&env, arg))
		i++;
	while (arg && arg[++i])
		env = ft_exec_cmd2(env, arg[i], arg, s);
	ft_tabdel(arg);
	return (env);
}
