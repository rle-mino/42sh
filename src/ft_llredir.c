/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/21 19:16:03 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/04 15:17:42 by dsonetha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		ll_err(char *s)
{
	int		i;

	i = -1;
	while (s && s[++i])
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
	ft_putendl_fd("42sh: error null argument near `<<'", 2);
	return (1);
}

t_e		*norme_got_me(t_e *env, char *s, int check, char *free_lol)
{
	char	*no_redir;
	char	*tmp;

	ft_strdel(&free_lol);
	no_redir = NULL;
	if (check == -1 && env)
	{
		env->status = 127;
		return (env);
	}
	no_redir = ft_str_trunc(s, '<');
	tmp = no_char(no_char(s, '<'), '<');
	if (ll_err(tmp))
	{
		ft_strdel(&no_redir);
		return (env);
	}
	env = ft_redir2(env, s, no_redir, NULL);
	return (env);
}

char	*add_rc(char *s)
{
	char	*new;

	if (s && (ft_strlen(s) - 1) > 0 && s[ft_strlen(s) - 1] != '\n')
		new = ft_strjoin(s, "\n");
	else
		return (s);
	ft_strdel(&s);
	return (new);
}

char	*print_llredir(char *end, char *line)
{
	char	*arg;
	char	*f;

	arg = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		if (get_next_line(1, &line) >= 0)
		{
			if (ft_strequ(line, end))
				break ;
			f = arg;
			arg = ft_strlink(arg, line, '\n');
			ft_strdel(&f);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (add_rc(arg));
}
