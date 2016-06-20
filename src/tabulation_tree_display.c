/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabulation_tree_display.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <ishafie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:28:03 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/31 17:44:28 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				afficher_mot(t_arbre *a, char *buf, int indice)
{
	if (a == NULL)
		return (0);
	buf[indice] = a->lettre;
	if (a->lettre == '\0')
	{
		buf[indice] = '\0';
		if (a->frered)
		{
			ft_putendl_fd(buf, get_fd(-1));
			afficher_mot(a->frered, buf, indice);
		}
		return (1);
	}
	if (a->filsg)
		afficher_mot(a->filsg, buf, indice + 1);
	if (a->frered)
	{
		ft_putendl_fd(buf, get_fd(-1));
		afficher_mot(a->frered, buf, indice);
	}
	return (indice);
}

int				afficher_chemin(t_arbre *a, char *buf, int indice)
{
	if (a == NULL)
		return (0);
	if (a->filsg)
	{
		buf[indice] = a->lettre;
		afficher_mot(a->filsg, buf, indice + 1);
		ft_putendl(buf);
		bzero(buf, indice);
	}
	if (a->frered)
	{
		afficher_chemin(a->frered, buf, indice);
	}
	return (indice);
}

int				afficher_alphabetique(t_arbre **a)
{
	char		*buf;
	int			len;

	if (!a || !*a)
		return (0);
	len = tgetnum("co");
	if (len <= 0)
		return (0);
	buf = (char*)malloc(sizeof(char) * len);
	if (!buf)
		exit(EXIT_FAILURE);
	afficher_chemin(*a, buf, 0);
	free(buf);
	return (0);
}
