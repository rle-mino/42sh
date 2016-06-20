/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:38:04 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 18:47:20 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_term_error(void)
{
	ft_putstr_fd("environment failure...\n", 2);
	exit(EXIT_FAILURE);
}

t_line			*start_edit_line(t_le *le, t_e *env)
{
	t_line		*inp;

	ft_prompt(env);
	signal(SIGINT, restart_prompt);
	signal(SIGWINCH, update_size);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	inp = edit_line(le);
	signal(SIGINT, sig_handler);
	return (inp);
}

t_le			*prepare_term(void)
{
	t_le			*le;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	le = ft_memalloc(sizeof(t_le));
	le->fd = get_fd(-1);
	le->w_sizex = w.ws_col;
	le->w_sizey = w.ws_row;
	reset_term();
	init_term();
	get_t_le(le);
	signal(SIGINT, sig_handler);
	return (le);
}

int				init_term(void)
{
	char				area[512];
	char				*tmp;
	char				*name_term;
	struct termios		term;
	static int			fd;

	fd = !fd ? open("/dev/tty", O_RDWR) : fd;
	if (fd == -1)
		fd = 2;
	get_fd(fd);
	tmp = area;
	if (tcgetattr(0, &term) == -1)
		init_term_error();
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		init_term_error();
	if (!(name_term = getenv("TERM")))
		init_term_error();
	if (tgetent(NULL, name_term) == ERR)
		init_term_error();
	tputs(tgetstr("am", &tmp), 1, ft_putint);
	tputs(tgetstr("xn", &tmp), 1, ft_putint);
	return (1);
}

int				reset_term(void)
{
	static struct termios		*reset;

	if (!reset)
	{
		reset = ft_memalloc(sizeof(struct termios));
		tcgetattr(0, reset);
	}
	tcsetattr(0, TCSADRAIN, reset);
	return (1);
}
