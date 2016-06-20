/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 21:07:27 by dsonetha          #+#    #+#             */
/*   Updated: 2016/03/18 21:09:13 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_get_argstr(char **t)
{
	char		*s;
	char		*tmp;
	int			i;

	i = 0;
	s = NULL;
	tmp = NULL;
	if (!t)
		return (NULL);
	while (t[i])
	{
		tmp = s;
		s = ft_strlink(s, t[i], ' ');
		ft_strdel(&tmp);
		i++;
	}
	return (s);
}

t_e		*exec_env_arg(char **t, t_e *env)
{
	char		*s;

	if (!env)
		return (env);
	if (ft_start_str(t[0], "setenv") || ft_start_str(t[0], "unsetenv"))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(t[0], 2);
		ft_putendl_fd(" command is forbidden", 2);
		return (env);
	}
	s = ft_get_argstr(t);
	env = ft_exec_cmd(s, env, -1);
	ft_strdel(&s);
	return (env);
}

char	**choose_your_print(char **t, char *env)
{
	int		i;
	int		j;
	int		check;

	j = 1;
	while (t[j])
	{
		i = 0;
		check = 1;
		while (env && t[j][i] && env[i] && t[j][i] == env[i])
		{
			if (t[j][i] && i > 0 && t[j][i] == '=')
			{
				ft_putendl_fd(t[j], 1);
				t[j][i] = '?';
				check = -1;
			}
			i++;
		}
		if (check == 1 && env)
			ft_putendl_fd(env, 1);
		j++;
	}
	return (t);
}

char	*go_homu(char *s1, char *s2)
{
	char	*new;

	if (s1)
		new = ft_strdup(s1);
	else
		new = ft_strdup(s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (new);
}

t_e		*set_shlvl(t_e *env)
{
	t_e		*temp;
	char	*tmp;
	int		i;

	temp = env;
	if (!env)
		return (env);
	while (temp && !ft_start_str("SHLVL=", temp->str))
		temp = temp->next;
	if (!temp && env)
		return (ft_add_e(env, "SHLVL=1"));
	i = ft_atoi(no_char(temp->str, '='));
	ft_strdel(&temp->str);
	tmp = ft_itoa(i + 1);
	temp->str = ft_strjoin("SHLVL=", tmp);
	ft_strdel(&tmp);
	return (env);
}
