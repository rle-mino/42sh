/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backslash_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 14:58:19 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/08 15:20:42 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_backslash_check(char const *s, int i)
{
	int		n;

	n = 0;
	if (!s || i < 0 || i > (int)ft_strlen(s))
		return (false);
	if (i - 1 >= 0 && s[i - 1] == '\\')
	{
		n++;
		i--;
		while (i - 1 >= 0 && s[i - 1] == '\\')
		{
			i--;
			n++;
		}
		if (n % 2 == 1)
			return (true);
	}
	return (false);
}
