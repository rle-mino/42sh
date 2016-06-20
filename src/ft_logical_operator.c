/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logical_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:57:48 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/04 15:35:19 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_e		*op_err(t_e *env, char c)
{
	if (env)
		env->status = 127;
	ft_putstr_fd("42sh: parse error near `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (env);
}

char	next_operator(char *s)
{
	int		i;

	i = -1;
	while (s && s[++i])
		if (s[i + 1] && (s[i] == '&' || s[i] == '|')
				&& s[i] == s[i + 1])
			return (s[i]);
	return ('\0');
}

t_e		*logical_exec(char *s, char op, t_e *env)
{
	char	*cmd;

	if (op != '\0')
		cmd = ft_sdouble_trunc(s, op);
	else
		cmd = s;
	env = ft_exec_cmd(cmd, env, -1);
	if (op != '\0')
		ft_strdel(&cmd);
	return (env);
}

t_e		*ft_logical_operator(char *s, t_e *env, int n)
{
	int		i;
	char	c;
	char	c2;
	char	*tmp;

	i = 0;
	if (!s || s[0] == '&' || s[0] == '|')
		return (op_err(env, s[0]));
	tmp = s;
	while (i <= n)
	{
		c = next_operator(tmp);
		if (i == 0)
			env = logical_exec(tmp, c, env);
		tmp = no_double_char(tmp, c);
		c2 = next_operator(tmp);
		if (c == '\0')
			break ;
		if (c == '&' && env->status == 0)
			env = logical_exec(tmp, c2, env);
		else if (c != '&' && env->status != 0)
			env = logical_exec(tmp, c2, env);
		i++;
	}
	return (env);
}
