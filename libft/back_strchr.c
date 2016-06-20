/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:37:10 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/14 19:05:47 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		skip_quote(const char *s, int *i, char c)
{
	*i = *i + 1;
	while (s[*i] && s[*i] != c)
		*i = *i + 1;
}

char		*back_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] && s[i] == 34)
			skip_quote(s, &i, 34);
		if (s[i] && s[i] == 39)
			skip_quote(s, &i, 39);
		if (s[i] == c && !ft_backslash_check(s, i))
			return ((char*)s + i);
	}
	if (s[i] == '\0' && c == 0)
		return ((char*)s + i);
	return (NULL);
}

char		*back_strchr_no_quote(const char *s, int c)
{
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == c && !ft_backslash_check(s, i))
			return ((char*)s + i);
	}
	if (s[i] == '\0' && c == 0)
		return ((char*)s + i);
	return (NULL);
}
