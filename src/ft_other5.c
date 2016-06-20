/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 14:30:36 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/03 16:45:11 by jaubard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**input_tab(t_i *inp, int l)
{
	char	**t;
	int		ind;
	t_i		*tmp;

	t = (char**)malloc(sizeof(char*) * (l + 2));
	tmp = inp;
	ind = 0;
	while (tmp)
	{
		t[ind] = ft_strdup(tmp->input);
		ind++;
		tmp = tmp->next;
	}
	t[ind] = ft_strdup("");
	t[ind + 1] = NULL;
	return (t);
}

t_valid	*init_valid(t_i *inp)
{
	t_valid	*new;

	ft_vprompt(1, NULL, 0);
	if (!(new = (t_valid*)malloc(sizeof(t_valid))))
		return (NULL);
	new->t = input_tab(inp, new->hd[2]);
	return (new);
}

void	get_salty(int i, char **s1, char **s2)
{
	char	*tmp;

	if (!i)
		return ;
	if (ft_strequ("", *s2))
		return ;
	tmp = *s1;
	*s1 = ft_strjoin(*s1, *s2);
	ft_strdel(&tmp);
	tmp = *s2;
	ft_strdel(&tmp);
	*s2 = ft_strdup("");
}

t_valid	*ft_vprompt(int i, t_valid *v, char c)
{
	char	*tmp;

	(void)c;
	if (i)
	{
		ft_putstr("\n> ");
		tmp = NULL;
		ft_putstr_fd(tgetstr("sc", &tmp), 0);
		ft_strdel(&tmp);
	}
	if (!v)
		return (NULL);
	return (v);
}

void	del_v(t_valid *v, int *hd)
{
	if (v)
	{
		ft_tabdel(v->t);
		free(v->hd);
		free(v);
	}
	if (hd)
		free(hd);
}
