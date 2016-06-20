/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 15:51:40 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/17 15:56:45 by jaubard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_builtin_clear(void)
{
	tputs(tgetstr("ho", NULL), 0, ft_putint);
	tputs(tgetstr("cd", NULL), 0, ft_putint);
}
