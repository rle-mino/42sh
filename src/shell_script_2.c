/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 17:39:25 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 20:53:42 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			sc_handler(int sig)
{
	(void)sig;
	kill(get_pid(-2), SIGKILL);
}

int				is_cdt(t_e **e, char **str)
{
	int			i;

	i = 0;
	if (!e || !*e)
		return (0);
	(*e)->op = 0;
	if (!str || !str[0] || !str[0][0] || !str[0][1] || !str[0][2])
		return (0);
	while (str[0][i] && ft_isspace(str[0][i]))
		i++;
	if (str[0][i] && str[0][i + 1] && str[0][i] == '[' && str[0][i + 1] == '['
	&& str[0][i + 2] && ft_isspace(str[0][i + 2]))
	{
		i += 2;
		while (str[0][i] && str[0][i] != ']')
			i++;
		if (str[0][i + 1] && str[0][i + 1] == ']')
		{
			(*e)->status = check_cdt(e, str, 0, -1);
			return (1);
		}
	}
	return (0);
}

int				define_ctrl_len(int ctrl, int *len)
{
	if (ctrl > 0 && ctrl <= 3)
		ctrl = 0;
	else if (ctrl == 5)
		ctrl = 1;
	else if (ctrl == 4)
		ctrl = 2;
	if (ctrl == 0 || ctrl == 1)
		*len = 4;
	else
		*len = 2;
	return (ctrl);
}

int				jump_ctrl(char **arg, int jump, int ctrl)
{
	static char	st_ctrl[3][5] = {"done", "fi", "esac"};
	int			len;
	int			i;
	int			maxlen;

	i = 0;
	len = 0;
	ctrl = define_ctrl_len(ctrl, &len);
	while (ctrl <= 5 && ctrl >= 0 && arg[jump] && arg[jump][i])
	{
		while (arg[jump][i] && ft_isspace(arg[jump][i]))
			i++;
		maxlen = i;
		while (arg[jump][maxlen])
			maxlen++;
		if (arg[jump] && arg[jump + i] &&
			(ft_strncmp(arg[jump] + i, st_ctrl[ctrl], len) ||
			((maxlen > len + i) && arg[jump][len + i])))
			break ;
		jump++;
	}
	return (jump);
}

t_e				*do_shell_script_and_follow(t_e *env, char **arg, int ctrl)
{
	int			jump;
	int			i;

	i = 0;
	jump = 0;
	do_shell_script(&env, arg, ctrl);
	if (!arg || !arg[0])
		return (env);
	find_correspondant(arg, 0, -2);
	jump = find_correspondant(arg, 0, ctrl);
	if (jump == -1)
		return (env);
	while (arg && arg[i])
		i++;
	if (jump >= i)
		return (env);
	jump = jump_ctrl(arg, jump, ctrl);
	return (exec_next_script(&env, arg + jump));
}
