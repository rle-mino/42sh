/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 17:44:38 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/06 16:38:51 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_cpy_tab(char **src)
{
	char		**cpy;
	int			i;

	i = 0;
	while (src[i])
		i++;
	cpy = ft_memalloc(sizeof(char *) * (i + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		cpy[i] = ft_strdup(src[i]);
		i++;
	}
	return (cpy);
}
