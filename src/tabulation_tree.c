/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabulation_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:26:57 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:27:41 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arbre.h"

t_arbre			*alloue_noeud(unsigned char val, t_arbre *fg, t_arbre *fd)
{
	t_arbre			*tmp;

	if (!(tmp = (t_arbre*)malloc(sizeof(struct s_noeud))))
		return (NULL);
	tmp->filsg = fg;
	tmp->frered = fd;
	tmp->lettre = val;
	return (tmp);
}

int				creer_arbre(t_arbre **a, char *name)
{
	struct dirent	*file;
	DIR				*folder;

	if (!name)
		return (0);
	folder = opendir(name);
	if (folder == NULL)
		return (0);
	while ((file = readdir(folder)) != NULL)
	{
		if (ft_strcmp(file->d_name, ".") != 0 &&
		ft_strcmp(file->d_name, "..") != 0)
			ajoute_mot(a, file->d_name);
	}
	return (1);
}

int				ajoute_mot_helper(t_arbre **a, char *str)
{
	t_arbre			*tmp;

	tmp = alloue_noeud(str[0], NULL, NULL);
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp->frered = *a;
	*a = tmp;
	if (str[0] == 0)
		return (1);
	return (ajoute_mot(&(*a)->filsg, &str[1]));
}

int				ajoute_mot(t_arbre **a, char *str)
{
	t_arbre			*tmp;

	tmp = NULL;
	if (!str)
		return (0);
	if (!(*a))
	{
		(*a) = alloue_noeud(str[0], NULL, NULL);
		if (str[0] == '\0')
			return (1);
		return (ajoute_mot(&(*a)->filsg, &str[1]));
	}
	if (str[0] == '\0')
	{
		(*a)->filsg = alloue_noeud(str[0], NULL, NULL);
		return (1);
	}
	if ((*a)->lettre > str[0])
		return (ajoute_mot_helper(a, str));
	if ((*a)->lettre == str[0])
		return (ajoute_mot(&(*a)->filsg, &str[1]));
	return (ajoute_mot(&(*a)->frered, str));
}
