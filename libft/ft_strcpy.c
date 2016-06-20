/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:21:28 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/16 23:55:36 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpy(char *dst, const char *src)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(src);
	while (++i <= len)
		dst[i] = src[i];
	return (dst);
}
