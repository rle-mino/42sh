/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 13:59:28 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/20 09:19:21 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

static void		display_time(void)
{
	time_t		rawtime;
	char		*tim;
	struct tm	*timeinfo;

	ft_putstr_fd(C_CYAN, get_fd(-1));
	ft_putchar_fd('[', get_fd(-1));
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	tim = asctime(timeinfo);
	ft_strclr(&tim[16]);
	ft_putstr_fd(&tim[11], get_fd(-1));
	ft_putstr_fd("] ", get_fd(-1));
	ft_putstr_fd("\033[0m", get_fd(-1));
}

static void		ft_get_hostname(char *str, char c)
{
	int			i;

	i = 0;
	ft_putchar_fd('e', get_fd(-1));
	while (str && str[++i] != c)
	{
		ft_putchar_fd(str[i], get_fd(-1));
		if (str[i] == c)
			break ;
	}
}

void			ft_prompt(t_e *env)
{
	char		hostname[128];

	gethostname(hostname, sizeof(hostname));
	display_time();
	if (open(".git", O_RDONLY) != -1)
		get_git(get_any_env_var(&env, "PWD"));
	print_git(env);
	ft_putstr_fd(C_YELLOW, get_fd(-1));
	ft_get_hostname(hostname, '.');
	ft_putstr_fd(C_WHITE, get_fd(-1));
	ft_putstr_fd(" ➩ ", get_fd(-1));
	ft_putstr_fd(C_BLUE, get_fd(-1));
	print_cwd(env);
	ft_putstr_fd("\033[1;37m\n❯❯❯ ", get_fd(-1));
	ft_putstr_fd("\033[00m", get_fd(-1));
}
