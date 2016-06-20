/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 14:00:23 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/08 15:51:47 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_nb(char const *s)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (s && s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] && !ft_isspace(s[i]))
		{
			while (s[i] && !ft_isspace(s[i]))
				i++;
			nb = nb + 1;
		}
	}
	return (nb);
}

char	*ft_word_malloc(char const *s, int st)
{
	char	*str;
	int		i;
	int		i2;

	i = 0;
	i2 = st;
	while (s[st] && !ft_isspace(s[st]))
	{
		st++;
		i++;
	}
	if (!(str = (char*)ft_memalloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i2] && !ft_isspace(s[i2]))
	{
		str[i] = s[i2];
		i++;
		i2++;
	}
	str[i] = '\0';
	return (epur_backslash(str));
}

int		ft_sp_start(char const *s, int i, int st)
{
	if (i != 0)
	{
		i = 1;
		while (i != 0)
		{
			while (s[st] && !ft_isspace(s[st]))
				st++;
			while (s[st] && ft_isspace(s[st]))
				st++;
			i--;
		}
	}
	else
		while (s[st] && ft_isspace(s[st]))
			st++;
	return (st);
}

char	**ft_cmdsplit(char const *s)
{
	int		nb;
	int		st;
	int		i;
	char	**tab;

	i = 0;
	st = 0;
	if (!s)
		return (NULL);
	nb = ft_word_nb(s);
	tab = (char**)ft_memalloc(sizeof(char*) * (nb + 1));
	if (!tab)
		return (NULL);
	while (i < nb)
	{
		st = ft_sp_start(s, i, st);
		tab[i] = ft_word_malloc(s, st);
		if (!tab[i])
			return (NULL);
		i++;
	}
	return (tab);
}
