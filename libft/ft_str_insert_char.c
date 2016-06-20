/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:47:19 by dsonetha          #+#    #+#             */
/*   Updated: 2016/05/26 19:10:52 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_insert_char(char *s, char c, int i)
{
	char	*new;
	int		j;
	int		len;

	len = ft_strlen(s) + 2;
	new = (char*)malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	ft_bzero(new, len);
	i += ft_strlen(s);
	j = -1;
	while (++j != i)
		new[j] = s[j];
	new[j] = c;
	while (s[i])
	{
		new[++j] = s[i];
		i++;
	}
	ft_strdel(&s);
	return (new);
}
