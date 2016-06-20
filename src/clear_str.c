/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:14:30 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/17 21:47:27 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*clear_str(char *str)
{
	int			i;
	int			j;
	char		*new;

	i = 0;
	j = 0;
	if (!str || (str[0] != '\'' && str[0] != '\"'))
		return (str);
	new = ft_memalloc(ft_strlen(str) + 10);
	while (str && str[++i + 1])
	{
		if (str[i] == '\\' && str[i + 1] == '\"')
			i++;
		new[j++] = str[i];
	}
	return (new);
}
