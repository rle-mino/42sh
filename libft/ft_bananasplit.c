/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bananasplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 22:49:21 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 22:41:29 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*get_next_word_space(char *str, int *i)
{
	int		j;
	char	*ret;

	j = *i;
	while (str[*i])
	{
		if (ft_isspace(str[*i]) || ((str[*i] == '\'' || str[*i] == '\"')
													&& str[*i - 1] != '\\'))
			break ;
		(*i)++;
	}
	ret = ft_strsub(str, j, *i - j);
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	return (ret);
}

char		*get_next_word_quotes(char *str, int *i, char stop)
{
	int		j;
	char	*ret;

	j = *i;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == stop && str[*i - 1] != '\\')
			break ;
		(*i)++;
	}
	ret = ft_strsub(str, j, *i - j + 1);
	if (str[*i])
		(*i)++;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	return (ret);
}

char		**ft_bananasplit(char *str)
{
	char	**words;
	int		i;
	int		k;

	words = ft_memalloc(sizeof(char *) * (ft_word_counter(str) + 1));
	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if ((str[i] == '\"' || str[i] == '\'') && (((i - 1) >= 0 &&
							str[i - 1] != '\\') || i == 0))
			words[k++] = get_next_word_quotes(str, &i, str[i]);
		else if (str[i] != '\"' && str[i] != '\'' && !ft_isspace(str[i]))
			words[k++] = get_next_word_space(str, &i);
	}
	return (words);
}
