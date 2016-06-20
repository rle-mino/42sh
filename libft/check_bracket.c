/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:38:54 by dsonetha          #+#    #+#             */
/*   Updated: 2015/11/30 17:24:01 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_bracket2(char *s, char c, char d)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == c)
			count++;
		else if (s[i] == d)
		{
			if (count == 0)
				return (2);
			count--;
		}
	}
	if (count != 0)
		return (0);
	return (1);
}

int	check_bracket(char *s)
{
	if (!s)
		return (-1);
	if (count_char(s, '"') % 2 != 0)
		return (0);
	if (count_char(s, '\'') % 2 != 0 || count_char(s, '`') % 2 != 0)
		return (0);
	if (!check_bracket2(s, '(', ')') || !check_bracket2(s, '[', ']'))
		return (0);
	if (!check_bracket2(s, '{', '}'))
		return (0);
	return (1);
}
