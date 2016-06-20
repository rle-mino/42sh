/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xenostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 16:00:58 by dsonetha          #+#    #+#             */
/*   Updated: 2015/05/07 16:08:44 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		xeno_count(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*ft_xenostr(char *s, char c)
{
	int		i;
	int		j;
	char	*xeno;

	i = xeno_count(s, c);
	if (!s || !(xeno = (char*)malloc(sizeof(char) * ft_strlen(s) - i + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			xeno[j] = s[i];
			j++;
		}
		i++;
	}
	xeno[j] = '\0';
	return (xeno);
}
