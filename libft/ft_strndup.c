/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 16:43:18 by dsonetha          #+#    #+#             */
/*   Updated: 2015/07/20 16:44:35 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*s2;
	int		i;

	if (!s1)
		return (NULL);
	s2 = (char*)malloc(sizeof(char) * n + 1);
	i = 0;
	if (!s2)
		return (NULL);
	while (s1[i] && i <= n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
