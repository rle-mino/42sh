/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_del_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 13:54:26 by dsonetha          #+#    #+#             */
/*   Updated: 2016/05/27 19:57:06 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_del_char(char *s, int i)
{
	char	*new;
	int		j;
	int		k;

	j = 0;
	k = -1;
	if (!(new = (char*)malloc(sizeof(char) * ft_strlen(s))))
		return (s);
	i = i + ft_strlen(s) - 1;
	while (s[++k])
	{
		if (k != i)
		{
			new[j] = s[k];
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}
