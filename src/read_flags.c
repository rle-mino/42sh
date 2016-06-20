/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 13:51:36 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/12 12:34:33 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_e		*read_export(char *s, char *s2, t_e *e)
{
	char	*tmp;
	char	*tmp2;

	if (!s2)
	{
		tmp = ft_strjoin("export ", s);
		e = call_builtins(tmp, e, 1);
		ft_strdel(&s);
	}
	else
	{
		tmp = ft_strjoin("\"", s2);
		tmp2 = ft_strjoin(tmp, "\"");
		ft_strdel(&tmp);
		tmp = ft_strjoin("export ", s);
		s = ft_strlink(tmp, tmp2, ' ');
		ft_strdel(&tmp2);
		e = ft_exec_cmd(s, e, -1);
		ft_strdel(&s);
	}
	ft_strdel(&tmp);
	return (e);
}

int		check_read_flags(char *s)
{
	char	**t;
	int		i;

	i = 0;
	if (!(t = ft_cmdsplit(s)))
		i = -1;
	else if (t[0] && t[1] && t[1][0] == '-')
	{
		if (ft_strequ(t[1], "-r"))
			i = 1;
		else
		{
			ft_putstr_fd(t[1], 2);
			ft_putendl_fd(": invalid option", 2);
			i = -1;
		}
	}
	ft_tabdel(t);
	return (i);
}

char	*no_backslash(char *s)
{
	int		i;
	int		n;
	char	*new;

	n = 0;
	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
		if (s[i] == '\\')
			n++;
	new = (char*)ft_memalloc(sizeof(char) * (ft_strlen(s) - n + 1));
	i = -1;
	n = 0;
	while (s[++i])
	{
		if (s[i] != '\\')
		{
			new[n] = s[i];
			n++;
		}
	}
	new[n] = '\0';
	ft_strdel(&s);
	return (new);
}

char	*read_input(void)
{
	char	*f;
	char	*tmp;
	char	*ret;
	int		check;

	tmp = NULL;
	ret = NULL;
	while ((check = get_next_line(0, &tmp)) != -1)
	{
		check = ft_strlen(tmp);
		if (check > 0)
			check--;
		if (tmp[check] == '\\')
			check = -2;
		f = ret;
		if (!ret)
			ret = ft_strdup(no_backslash(tmp));
		else
			ret = ft_strjoin(ret, no_backslash(tmp));
		if (check != -2)
			break ;
	}
	if (check == -1)
		return (NULL);
	return (ret);
}

t_e		*read_no_flags(char *cmd, t_e *e)
{
	char	**word;
	char	**input;
	char	*line;

	line = read_input();
	input = NULL;
	word = NULL;
	if (!line || !(word = ft_cmdsplit(last_word(cmd, 1)))
		|| !(input = ft_cmdsplit(line)) || !word[0])
	{
		e->status = clean_read(word, input, line, 1);
		return (e);
	}
	return (ft_read2(word, input, line, e));
}
