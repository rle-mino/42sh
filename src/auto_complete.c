/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 22:55:43 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/16 14:15:19 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"
#include "arbre.h"

void			free_arbre(t_arbre **a)
{
	if (!(*a))
		return ;
	if (a == NULL)
		return ;
	(*a)->lettre = 0;
	if ((*a)->filsg)
		free_arbre(&(*a)->filsg);
	if ((*a)->frered)
		free_arbre(&(*a)->frered);
	free(*a);
	(*a) = NULL;
}

static int		is_folder(char *path, char *name, char *buffer)
{
	struct stat		statb;
	int				folder;
	char			*all;
	char			*tmp;

	all = ft_strjoin(path, name);
	tmp = ft_strjoin(all, buffer);
	free(all);
	folder = stat(tmp, &statb);
	if (!folder && S_ISDIR(statb.st_mode) && tmp[ft_strlen(tmp) - 1] != '/')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char			**get_path_and_word(char *str)
{
	int			i;
	char		**path_and_word;

	i = ft_strlen(str) - 1;
	path_and_word = ft_memalloc(sizeof(char *) * 2);
	while (i >= 0)
	{
		if (str && str[i] == '/')
		{
			path_and_word[0] = ft_strsub(str, 0, i + 1);
			path_and_word[1] = ft_strdup(str + i + 1);
			return (path_and_word);
		}
		i--;
	}
	path_and_word[0] = ft_strdup("./");
	path_and_word[1] = ft_strdup(str);
	return (path_and_word);
}

static char		**get_actual_word(t_line *line)
{
	char		buffer[1024];
	char		**path_and_word;
	int			i;

	i = 0;
	ft_bzero(buffer, sizeof(buffer));
	while (line && line->prev && line->c != ' ')
		line = line->prev;
	if (line && (line->c == ' ' || line->c == '\0'))
		line = line->next;
	while (line && line->c != ' ')
	{
		buffer[i] = line->c;
		i++;
		line = line->next;
	}
	path_and_word = get_path_and_word(buffer);
	return (path_and_word);
}

void			complete_word(t_line **line, t_le *le)
{
	char		**path_and_word;
	char		*buffer;
	t_arbre		*arbre;
	t_arbre		*tmp;
	int			i;

	i = -1;
	(void)le;
	arbre = NULL;
	path_and_word = get_actual_word(*line);
	buffer = ft_memalloc(sizeof(char) * 1024);
	creer_arbre(&arbre, path_and_word[0]);
	tmp = arbre;
	arbre = recherche(&arbre, path_and_word[1]);
	completion_tree(arbre, &buffer, 0);
	if (buffer[0] == '\0')
		advanced_completion(le, path_and_word);
	while (buffer[++i])
		add_to_line(le, line, buffer[i]);
	if (is_folder(path_and_word[0], path_and_word[1], buffer))
		add_to_line(le, line, '/');
	free_autocomplete(tmp, buffer, path_and_word);
}
