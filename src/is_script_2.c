/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 22:40:23 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/17 22:02:48 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_structure_boucle(char *boucle)
{
	int		i;

	i = 0;
	if (!boucle)
		return (0);
	while (boucle[i] && ft_isspace(boucle[i]))
		i++;
	if (ft_strncmp(boucle + i, "for", 3) == 0 && ft_isspace(boucle[3 + i]))
		return (FOR);
	if (ft_strncmp(boucle + i, "while", 5) == 0 && ft_isspace(boucle[5 + i]))
		return (WHILE);
	if (ft_strncmp(boucle + i, "until", 5) == 0 && ft_isspace(boucle[5 + i]))
		return (UNTIL);
	return (0);
}
