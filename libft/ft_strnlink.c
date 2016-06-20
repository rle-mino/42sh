/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlink.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 19:51:30 by dsonetha          #+#    #+#             */
/*   Updated: 2015/04/02 20:14:32 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnlink2(char *s, char *str, int len)
{
	int		i;

	i = 0;
	while (s[i] && i < len)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*ft_strnlink_err(char *s, int len)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if ((int)ft_strlen(s) > len)
		size = len;
	if (!(ret = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (s[i] && i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strnlink(char *s1, char *s2, char c, int len)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (ft_strnlink_err(s2, len));
	if (!s2 || !(str = (char*)malloc(sizeof(char) * (ft_strlen(s1)
						+ ft_strlen(s2)))))
		return (NULL);
	i = 0;
	j = 0;
	str = ft_strnlink2(s1, str, len);
	while (s1[i] && i < len)
		i++;
	str[i] = c;
	i++;
	while (s2[j] && i < len && i + j < len)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
