/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdouble_trunc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 19:06:54 by dsonetha          #+#    #+#             */
/*   Updated: 2016/05/28 12:33:35 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sdouble_trunc(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		i++;
		if (s[i] == c && s[i + 1] && s[i + 1] == c)
			break ;
	}
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
		if (s[i] == c && s[i + 1] && s[i + 1] == c)
			break ;
	}
	str[i] = '\0';
	return (str);
}
