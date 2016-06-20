/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_quote_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 18:18:42 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/14 19:07:44 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		spec_char(char c)
{
	if (c == '`' || c == '|' || c == '>' || c == '<'
		|| c == '[' || c == ']')
		return (1);
	if (c == '$')
		return (2);
	return (0);
}

static void		add_slash(char *str, int *id)
{
	str[*id] = 92;
	*id = *id + 1;
}

static void		add_quote(char *str, int *id)
{
	str[*id] = '\'';
	str[*id + 1] = '$';
	str[*id + 2] = '\'';
	*id = *id + 3;
}

char			*replace_space(char *str)
{
	int			i;
	int			id;
	char		*newstr;

	i = 0;
	id = 0;
	if (!str)
		return (NULL);
	newstr = (char*)ft_memalloc(sizeof(char) * ft_strlen(str) * 2);
	while (newstr && str[i])
	{
		if (spec_char(str[i]) == 1)
			add_slash(newstr, &id);
		else if (spec_char(str[i]) == 2)
			add_quote(newstr, &id);
		newstr[id] = str[i];
		id++;
		i++;
	}
	ft_strdel(&str);
	newstr[id - 1] = 0;
	return (newstr);
}
