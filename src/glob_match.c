/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 18:13:16 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/13 20:30:22 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		glob_cubra(char *a, char *b, int *i, int *j)
{
	char	**split;
	int		k;
	int		ret;
	char	*tmp;

	(*i)++;
	k = 0;
	ret = 0;
	split = ft_strsplit(a + *i, ',');
	while (a[*i] != '}')
		(*i)++;
	(*i)++;
	while (split[k])
	{
		if (!ret && (tmp = ft_strchr(split[k], '}')))
			tmp[0] = 0;
		if (!ret)
			ret = check_match(split, b, j, k);
		free(split[k]);
		k++;
	}
	free(split);
	return (ret);
}

int		glob_any(char *b, int *i, int *j)
{
	if (b[*j])
	{
		(*j)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int		glob_bra(char *a, char *b, int *i, int *j)
{
	char	*gab;

	gab = poss_in_bra(a, i);
	if (ft_strchr(gab, b[*j]))
	{
		free(gab);
		(*j)++;
		return (1);
	}
	free(gab);
	return (0);
}

int		glob_star(char *a, char *b, int *i, int *j)
{
	while (a[*i] == '*' && a[*i])
		(*i)++;
	while (b[*j] != a[*i] && b[*j])
		(*j)++;
	if (!b[*j] && a[*i])
		return (0);
	return (1);
}

int		match(char *a, char *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (b[j] && a[i])
	{
		if (a[i] == '*' && !glob_star(a, b, &i, &j))
			return (0);
		else if (a[i] == '[' && !glob_bra(a, b, &i, &j))
			return (0);
		else if (a[i] == '?' && !glob_any(b, &i, &j))
			return (0);
		else if (a[i] == '{' && !glob_cubra(a, b, &i, &j) && i != 0)
			return (0);
		else if (a[i] && b[j] && a[i] == b[j])
		{
			i++;
			j++;
		}
		else if (a[i] && b[j] && a[i] != b[j] && !is_glob_char(a[i]))
			return (0);
	}
	return ((a[i] == '\0' && b[j] == '\0') || a[i] == '*' ? j : 0);
}
