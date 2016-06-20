/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 18:01:50 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 18:01:54 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**boucle_go_home(char **t, int i, t_e *temp, char *s)
{
	while (t && t[i])
	{
		if (t[i][0] == '~' && temp)
		{
			s = ft_strdup(temp->str + 5);
			t[i] = ft_go_home2(t[i], s);
		}
		i++;
	}
	return (t);
}

char			**ft_go_home(char **t, t_e *home, int i)
{
	char		*s;
	t_e			*temp;
	char		*var;
	int			a;

	var = NULL;
	s = NULL;
	a = 0;
	while (t && t[a])
	{
		t[a] = clear_str(t[a]);
		a++;
	}
	temp = home;
	if (!t)
		return (NULL);
	while (temp && ft_start_str("HOME=", temp->str) == 0)
		temp = temp->next;
	t = boucle_go_home(t, i, temp, s);
	if (t[0] && t[1])
		t[1] = ft_get_oldpwd(t[1], home);
	return (t);
}
