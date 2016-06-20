/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:52:02 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 18:04:55 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word	*filter_match(char *comp, t_word *words)
{
	t_word	*tmp;

	if (!words)
		return (NULL);
	if (words && !match(comp, words->word))
	{
		tmp = words;
		words = filter_match(comp, words->next);
		free(tmp->word);
		free(tmp);
	}
	else
		words->next = filter_match(comp, words->next);
	return (words);
}

static char		*replace_by_poss(char *word)
{
	char	**path_and_word;
	t_word	*poss;

	path_and_word = get_path_and_word(word);
	if (!path_and_word)
		return (ft_strdup(""));
	poss = NULL;
	if (ft_strstr(word, "**/*") == word)
	{
		poss = get_files("./");
		free(path_and_word[0]);
		path_and_word[0] = ft_strdup("./");
		if (poss)
			get_files_recu(poss);
	}
	else
		poss = get_files(path_and_word[0]);
	if (poss && ((path_and_word[1][0] != '*' && path_and_word[1][0])
												|| path_and_word[1][0] == '*'))
		poss = filter_match(path_and_word[1], poss);
	free(word);
	return (merge_word(poss, path_and_word[0]));
}

char			*ft_glob(char *line)
{
	char	**split;
	char	*merge;
	int		i;

	split = ft_bananasplit(line);
	i = -1;
	while (split[++i])
	{
		if (!(split[i][0] == '\"') && !(split[i][0] == '\'') &&
														split[i][0] != '$')
		{
			if (ne_glob(split[i]))
				split[i] = replace_by_poss(split[i]);
		}
	}
	merge = merge_split(split);
	ft_tabdel(split);
	free(line);
	return (merge);
}
