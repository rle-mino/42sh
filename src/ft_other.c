/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:11:28 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/17 12:10:43 by jaubard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_env(char **t, t_e *env)
{
	t_e		*temp;

	temp = env;
	if (t && t[1])
	{
		if (ft_strequ(t[1], "-i"))
			ft_env_args(&t[1], NULL);
		else
			ft_env_args(t, env);
	}
	else
	{
		while (temp)
		{
			ft_putendl(temp->str);
			temp = temp->next;
		}
	}
}

t_e		*ft_setenv(char **t, t_e *env, int i, int check)
{
	t_e		*temp;

	temp = env;
	while (t && t[i])
		i++;
	if (i != 3 && i != 4 && env)
		env->status = ft_print_error("", "setenv", i);
	else if (t)
	{
		while (temp)
		{
			if (ft_start_str(t[1], temp->str))
				return (ft_change_env(env, temp, t, check));
			temp = temp->next;
		}
		return (ft_add_env(t, env, check));
	}
	return (env);
}

t_e		*ft_unsetenv_error(char **t, t_e *env)
{
	if (!t[1])
		ft_putendl_fd("unsetenv error: no arguments to unset", 2);
	if (t[1] && t[2])
		ft_putendl_fd("unsetenv error: too many arguments", 2);
	if (env)
		env->status = 1;
	return (env);
}

t_e		*ft_unsetenv(char **t, t_e *env, int i)
{
	t_e		*temp;

	temp = env;
	if (t && t[0] && ((t[1] && t[2]) || !t[1]))
		env = ft_unsetenv_error(t, env);
	else
	{
		while (temp)
		{
			if (ft_start_str(t[1], temp->str)
					&& temp->str[ft_strlen(t[1])] == '=')
				break ;
			temp = temp->next;
		}
		if (!temp && i == 1)
		{
			ft_putendl_fd("unsetenv error: nothing to unset", 2);
			if (env)
				env->status = 1;
		}
		else if (temp)
			env = ft_del_env(t[1], env);
	}
	return (env);
}
