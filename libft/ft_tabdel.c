/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 17:31:02 by dsonetha          #+#    #+#             */
/*   Updated: 2015/04/30 16:52:57 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_tabdel(char **as)
{
	int		i;

	i = 0;
	if (as == NULL)
		return ;
	while (as[i])
	{
		if (as[i])
			free(as[i]);
		as[i] = NULL;
		i++;
	}
	free(as);
	as = NULL;
}
