/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 15:20:01 by dsonetha          #+#    #+#             */
/*   Updated: 2016/03/21 15:56:07 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfill(char *s, char *fill, int off)
{
	char	*new;
	int		i;
	int		save;

	if (!s || !fill
			|| !(new = (char*)malloc(sizeof(char) * ft_strlen(s)
					+ ft_strlen(fill) + 2)))
		return (NULL);
	off += ft_strlen(s);
	save = off - 1;
	new = ft_strncpy(new, s, off);
	i = -1;
	off--;
	while (fill[++i])
		new[++off] = fill[i];
	while (s[++save])
		new[++off] = s[save];
	new[++off] = '\0';
	return (new);
}
