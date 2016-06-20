/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 21:36:38 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 23:40:25 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_glob_char(char c)
{
	return (c == '[' || c == ']' || c == '*' || c == '?' || c == '{'
																|| c == '}');
}

void			add_to_poss(char *poss, int *i, char a, char b)
{
	while (a < b && *i < 1024)
	{
		poss[*i] = a;
		a++;
		(*i)++;
	}
}

char			*poss_in_bra(char *a, int *i)
{
	char	*poss;
	int		j;

	(*i)++;
	j = 0;
	poss = ft_memalloc(1024);
	while (a[*i] && a[*i] != ']')
	{
		if (a[*i] != '-')
			poss[j++] = a[*i];
		else if (a[*i] == '-' && (i - 1) >= 0 && a[*i + 1])
			add_to_poss(poss, &j, a[*i - 1], a[*i + 1]);
		(*i)++;
	}
	(*i)++;
	return (poss);
}

char			*merge_split(char **split)
{
	int		i;
	char	*merge;
	char	*tmp;

	i = -1;
	merge = ft_memalloc(1);
	while (split[++i])
	{
		if (ft_strlen(merge) > 0)
		{
			tmp = merge;
			merge = ft_strjoin(merge, " ");
			free(tmp);
		}
		tmp = merge;
		merge = ft_strjoin(merge, split[i]);
		free(tmp);
	}
	return (merge);
}

char			*merge_word(t_word *words, char *path)
{
	char	*new_split;
	char	*tmp;

	new_split = ft_memalloc(1);
	while (words)
	{
		if (ft_strlen(new_split) > 0)
		{
			tmp = new_split;
			new_split = ft_strjoin(new_split, " ");
			free(tmp);
		}
		glob_add_word(&new_split, path, words);
		words = words->next;
	}
	clear_words(words);
	return (new_split);
}
