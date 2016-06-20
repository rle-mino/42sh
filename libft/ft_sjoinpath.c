/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sjoinpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 15:12:15 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/10 15:13:25 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sjoinpath(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		i2;

	if (!s1 || !s2 || !(str = (char*)ft_memalloc(sizeof(char)
					* (ft_strlen(s1) + ft_strlen(s2) + 2))))
		return (NULL);
	i = 0;
	i2 = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (s2[i2])
	{
		str[i] = s2[i2];
		i++;
		i2++;
	}
	return (str);
}
