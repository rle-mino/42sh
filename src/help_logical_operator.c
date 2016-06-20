/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_logical_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 18:29:09 by dsonetha          #+#    #+#             */
/*   Updated: 2016/05/28 14:23:17 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		count_op(char *s)
{
	int		count;
	char	*tmp;
	char	c;

	if (!s)
		return (0);
	tmp = s;
	count = 0;
	c = next_operator(tmp);
	while (c != '\0')
	{
		tmp = no_double_char(tmp, c);
		c = next_operator(tmp);
		count++;
	}
	return (count);
}
