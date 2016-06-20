/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 18:33:23 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/15 15:03:04 by jaubard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		count_word(char **t)
{
	int		n;

	n = 0;
	if (!t)
		return (-1);
	while (t[n])
		n++;
	return (n);
}

int		clean_read(char **t, char **t2, char *s, int i)
{
	ft_tabdel(t);
	ft_tabdel(t2);
	ft_strdel(&s);
	return (i);
}

char	*last_word(char *s, int nw)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (nw == 0)
		return (ft_strtrim(s));
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (nw > 0)
	{
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		nw--;
	}
	if (!s[i])
		return ("");
	return (ft_strtrim(s + i));
}

t_e		*ft_read2(char **word, char **input, char *line, t_e *e)
{
	int		check;
	int		nw;
	int		ni;
	int		i;
	char	*tmp;

	check = 0;
	nw = count_word(word);
	ni = count_word(input);
	i = 0;
	while (i + 1 != nw && i != ni)
	{
		e = ft_help_read(e, word[i], input[i], NULL);
		i++;
	}
	if (i + 1 == nw && i != ni)
	{
		tmp = last_word(line, i);
		e = ft_help_read(e, tmp, word[i], "non");
	}
	else
		e = empty_export(e, i, nw, word);
	e->status = clean_read(word, input, line, check);
	return (e);
}

t_e		*ft_read(char *cmd, t_e *e)
{
	char	**word;
	char	**input;
	char	*line;
	int		check;

	line = NULL;
	word = NULL;
	input = NULL;
	if ((check = check_read_flags(cmd)) == 0)
		return (read_no_flags(cmd, e));
	if (check == -1 || (get_next_line(0, &line)) == -1)
	{
		e->status = 1;
		return (e);
	}
	if (!line || !(word = ft_cmdsplit(last_word(cmd, 2)))
		|| !(input = ft_cmdsplit(line)) || !word[0])
	{
		e->status = clean_read(word, input, line, 1);
		return (e);
	}
	return (ft_read2(word, input, line, e));
}
