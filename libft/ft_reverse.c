/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/14 09:32:10 by dsonetha          #+#    #+#             */
/*   Updated: 2015/06/14 09:33:45 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse(char *str, int len)
{
	int		i;
	char	ch;

	i = -1;
	while (++i <= (len - 1) / 2)
	{
		ch = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = ch;
	}
}
