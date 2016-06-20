/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 18:31:00 by dsonetha          #+#    #+#             */
/*   Updated: 2015/06/14 09:29:51 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr(void const *p)
{
	unsigned long	adr;
	char const		*base;
	char			res[9];
	int				i;

	adr = (unsigned long)p;
	base = "0123456789abcdef";
	i = 8;
	while ((adr / 16) > 0 || i >= 8)
	{
		res[i] = base[(adr % 16)];
		adr /= 16;
		i--;
	}
	res[i] = base[(adr % 16)];
	ft_putstr("0x");
	while (i < 9)
	{
		ft_putchar(res[i]);
		i++;
	}
}
