/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_backslash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 15:34:06 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/12 11:38:25 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		epur_len(char *s)
{
	int		i;
	int		n;

	n = 0;
	i = -1;
	while (s[++i])
		if (s[i] == '\\' && !ft_backslash_check(s, i))
		{
			n++;
		}
	return (i - n + 1);
}

char	*epur_backslash(char *s)
{
	int		i;
	int		n;
	char	*new;

	if (!s || !(new = ft_memalloc(sizeof(char) * epur_len(s))))
		return (NULL);
	i = -1;
	n = 0;
	while (s[++i])
	{
		if (s[i] != '\\')
		{
			new[n] = s[i];
			n++;
		}
		else if (s[i + 1] && s[i + 1] == '\\')
		{
			i++;
			new[n] = s[i];
			n++;
		}
	}
	ft_strdel(&s);
	return (new);
}
