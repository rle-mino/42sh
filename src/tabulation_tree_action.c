/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabulation_tree_action.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:29:56 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:30:20 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arbre.h"

void			completion_tree(t_arbre *a, char **mot, int i)
{
	if (!a)
		return ;
	(*mot)[i] = a->lettre;
	if (a->lettre == 0 || a->frered)
	{
		(*mot)[i] = 0;
		return ;
	}
	if (a->filsg)
		completion_tree(a->filsg, mot, i + 1);
}

t_arbre			*recherche(t_arbre **a, char *mot)
{
	if (!mot)
		return (NULL);
	if (!(*a))
		return (NULL);
	if (mot[0] == '\0' || (*a)->lettre == '\0')
		return (*a);
	if ((*a)->lettre > mot[0])
		return (NULL);
	if ((*a)->lettre < mot[0])
		return (recherche(&(*a)->frered, mot));
	if ((*a)->lettre == mot[0])
		return (recherche(&(*a)->filsg, mot + 1));
	return (NULL);
}
