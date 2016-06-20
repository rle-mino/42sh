/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/23 16:59:48 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/14 17:53:02 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGQUIT || signo == SIGTSTP || signo == SIGINT)
		return ;
	else if (signo == SIGWINCH)
		ioctl(0, TIOCSTI, "");
}

void	update_size(int sig)
{
	t_le			*le;
	struct winsize	w;
	t_line			*tmp;
	t_e				*e;

	(void)sig;
	le = get_t_le(NULL);
	e = get_t_env(NULL);
	ioctl(0, TIOCGWINSZ, &w);
	if (le)
	{
		le->w_sizex = w.ws_col;
		le->w_sizey = w.ws_row;
		tmp = le->line;
		while (le->line->prev)
			move_left(le, &(le->line));
		tputs(tgetstr("cl", NULL), 1, ft_putint);
		ft_prompt(e);
		redisplay_line(le->line->next, le);
		le->sig = 1;
	}
}

void	stop_heredoc(int sig)
{
	t_le			*le;

	(void)sig;
	le = get_t_le(NULL);
	if (le)
	{
		le->sig = 1;
		history(RES_ORI, NULL);
		le->pos_x = 4;
	}
}

void	restart_prompt(int sig)
{
	t_le			*le;
	t_e				*e;

	(void)sig;
	e = get_t_env(NULL);
	if (!e)
		return ;
	le = get_t_le(NULL);
	ft_putchar_fd('\n', get_fd(-1));
	ft_prompt(get_t_env(NULL));
	if (le && le->line)
	{
		clear_line(get_first_line(le->line));
		le->line = ft_memalloc(sizeof(t_line));
		le->line->is_orig = 1;
		history(RES_ORI, NULL);
		le->pos_x = 4;
	}
}
