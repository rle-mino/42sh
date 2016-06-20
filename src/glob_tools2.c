/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 14:25:46 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 23:38:25 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	glob_add_word(char **new_split, char *path, t_word *words)
{
	char	*tmp;

	tmp = (*new_split);
	(*new_split) = ft_strjoin((*new_split), "\"");
	free(tmp);
	tmp = (*new_split);
	(*new_split) = ft_strjoin((*new_split), path);
	free(tmp);
	tmp = (*new_split);
	(*new_split) = ft_strjoin((*new_split), words->word);
	free(tmp);
	tmp = (*new_split);
	(*new_split) = ft_strjoin((*new_split), "\"");
	free(tmp);
}

int		ne_glob(char *split)
{
	if (ft_strchr(split, '*') || ft_strchr(split, '?') || ft_strchr(split, '{'))
		return (1);
	if (ft_strchr(split, '[') && ft_strcmp(split, "[[") &&
												ft_strcmp(split, "["))
		return (1);
	return (0);
}

int		check_match(char **split, char *b, int *j, int k)
{
	if (ft_strstr(b + *j, split[k]) == b + *j)
	{
		follow_match(b, j, split, k);
		return (1);
	}
	return (0);
}

void	follow_match(char *b, int *j, char **split, int k)
{
	int		l;

	l = 0;
	while (split[k][l] && b[*j])
	{
		(*j)++;
		l++;
	}
}
