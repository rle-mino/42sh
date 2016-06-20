/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 15:16:33 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/16 23:31:27 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_word(char const *s, char c)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	while (s[i] && s[i] == c && !ft_backslash_check(s, i))
	{
		i++;
	}
	while (s[i])
	{
		if ((s[i] != c) || (s[i] == c && ft_backslash_check(s, i)))
			k++;
		while (s[i]
				&& (s[i] != c || (s[i] == c && ft_backslash_check(s, i))))
			i++;
		if (s[i] == c && !ft_backslash_check(s, i))
			i++;
	}
	return (k);
}

static char		*nblet(char const *s, char c, const int j)
{
	int			i;
	int			k;
	int			m;
	int			o;

	m = j;
	k = 0;
	i = 0;
	while (m >= 0)
	{
		while (s[i] && s[i] == c && !ft_backslash_check(s, i))
			i++;
		while (s[i] && (s[i] != c
					|| (s[i] == c && ft_backslash_check(s, i))) && m > 0)
			i++;
		m--;
	}
	o = i;
	while (s[i] && (s[i] != c || (s[i] == c && ft_backslash_check(s, i))))
	{
		k++;
		i++;
	}
	return (ft_strsub(s, o, k));
}

char			**ft_backsplit(char const *s, char c)
{
	int			i;
	char		**tab;
	int			j;

	if (!s)
		return (NULL);
	j = 0;
	i = nb_word(s, c);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (i)
	{
		tab[j] = nblet(s, c, j);
		i--;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
