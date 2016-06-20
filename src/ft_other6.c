/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 10:58:51 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/16 12:58:23 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int							ft_echo(char **args, int status)
{
	int		i;

	i = 1;
	while (args && args[0] && args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (status == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}

static void					ft_cd2(int *i, char **t, t_e *temp, t_e *env)
{
	*i = -1;
	if (t && t[0] && t[1] && ft_strequ(t[1], "-"))
		ft_putendl_fd("cd error: oldpwd not set", 2);
	else if (!temp)
		ft_putendl_fd("cd error: home not set", 2);
	else if (temp && (*i = chdir(temp->str + 5)) == -1)
		ft_print_error(temp->str + 5, "cd", 0);
	env->status = 1;
}

t_e							*ft_cd(char **t, t_e *env, int i, char *str)
{
	t_e		*temp;

	temp = env;
	while (temp && ft_start_str("HOME=", temp->str) == 0)
		temp = temp->next;
	t = ft_go_home(t, env, 0);
	if (t && t[1] && t[2])
	{
		ft_putendl_fd("cd error: too many arguments", 2);
		i = -1;
	}
	else if (t && (!t[1] || (t[1] && ft_strequ(t[1], "-"))))
		ft_cd2(&i, t, temp, env);
	else if ((i = chdir(t[1])) == -1 && env)
		env->status = ft_print_error(t[1], "cd", 0);
	return (ft_change_pwd(env, str, i, t[1]));
}
