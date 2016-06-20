/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:45:30 by dsonetha          #+#    #+#             */
/*   Updated: 2014/11/08 14:31:54 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	while (dst[i])
		i++;
	while (src[i2] && i < size)
	{
		dst[i] = src[i2];
		i++;
		i2++;
	}
	i--;
	dst[i] = '\0';
	return (ft_strlen(dst));
}
