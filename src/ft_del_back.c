/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 11:40:39 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/20 11:45:07 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_del_back(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new = ft_memalloc(ft_strlen(str) + 2);
	while (str[i])
	{
		if (str[i] != '\\')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}
