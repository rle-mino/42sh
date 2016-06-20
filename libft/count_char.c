/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 16:05:29 by dsonetha          #+#    #+#             */
/*   Updated: 2015/07/20 16:07:04 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_char(char *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
		if (s[i] == c)
			count++;
	return (count);
}
