/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/30 10:59:32 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/13 15:37:57 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		clear_pipe(char **t, int i)
{
	int		j;

	j = -1;
	if (i > 0 && t[i - 1][ft_strlen(t[i - 1])] == '|' && t[i][0] == '&')
		return (1);
	while (t[i][++j])
		if (t[i][j] == '&' && j > 0 && t[i][j - 1] == '|')
			return (1);
	return (-1);
}

void	print_pipe(char *s, char *print, int i, int check)
{
	char	*tmp;
	char	*fuck;

	fuck = s;
	while (s && s[++i] && check < count_char(s, '|') - 1)
	{
		if (s[i] == '|')
			check++;
		if (s[i] == '|')
			fuck = no_char(fuck, '|');
		tmp = print;
		if (s[i] == '|' && s[i + 1] && s[i + 1] == '&')
			print = ft_strjoin(print, "errpipe ");
		else if (s[i] == '|')
			print = ft_strjoin(print, "pipe ");
		if (!ft_strequ(tmp, print))
			ft_strdel(&tmp);
	}
	if (print)
		ft_putstr(print);
	if (ft_strchr(no_char(fuck, '|'), '&') != NULL)
		ft_putstr("err");
	ft_putstr("pipe> ");
	ft_strdel(&print);
}

char	*final_flash(char *s)
{
	if (s && s[0] == '&')
		return (no_char(s, '&'));
	return (s);
}

void	ft_clean_env(t_e *env)
{
	t_e		*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_clean_exit(int i, char *cmd, char **arg, t_e *env)
{
	history(FIRST_HIST, NULL);
	history(WRITE_HIST, NULL);
	close(get_fd(-1));
	if (cmd)
		ft_strdel(&cmd);
	if (arg)
		ft_tabdel(arg);
	if (env)
		ft_clean_env(env);
	exit(i);
}
