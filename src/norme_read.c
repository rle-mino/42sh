/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 15:36:37 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/12 12:45:50 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*help_read2(char *s)
{
	int		i;
	int		c;
	char	*ret;

	c = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s) - 1;
	while (i > 0 && s[i] == '\\')
	{
		i--;
		c++;
	}
	if (c % 2 == 0)
		return (s);
	ret = ft_strjoin(s, "\\");
	ft_strdel(&s);
	return (ret);
}

t_e		*ft_help_read(t_e *env, char *s, char *inp, char *tmp)
{
	if (s[0] == '-')
		env->status = read_error(s);
	else
	{
		if (!tmp)
			env = read_export(ft_strlink(s, inp, ' '), NULL, env);
		else
			env = read_export(inp, help_read2(s), env);
	}
	return (env);
}

t_e		*empty_export(t_e *e, int i, int nw, char **word)
{
	while (i != nw)
	{
		e = read_export(ft_strlink(word[i], "", ' '), NULL, e);
		i++;
	}
	return (e);
}
