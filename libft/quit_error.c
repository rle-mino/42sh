/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 18:01:58 by dsonetha          #+#    #+#             */
/*   Updated: 2016/05/28 14:08:50 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	quit_error(char *s)
{
	ft_putendl(s);
	exit(-1);
}
