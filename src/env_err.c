/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 09:11:38 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/20 09:12:21 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

int		env_err(void)
{
	ft_putstr_fd(C_RED, get_fd(-1));
	ft_putendl_fd("Environnement vide, le programme ne peut fonctionner",
	get_fd(-1));
	ft_putendl_fd("Fermeture !", get_fd(-1));
	return (0);
}
