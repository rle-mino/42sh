/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_first_method_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:11:57 by ishafie           #+#    #+#             */
/*   Updated: 2016/06/18 19:30:23 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				test_cdt_alpha_if(char **hook)
{
	if (!ft_strcmp(hook[1], "=") && !ft_strcmp(hook[0], hook[2]))
		return (0);
	if (!ft_strcmp(hook[1], "!=") && ft_strcmp(hook[0], hook[2]))
		return (0);
	return (1);
}

int				test_cdt_if(char **hook)
{
	int			cdt;

	if (!hook[0] || !hook[1] || !hook[2] || hook[3])
		return (1);
	cdt = check_condition_if(hook, 1);
	if (cdt == 10)
		return (test_cdt_num_if(hook));
	else if (cdt == 5)
		return (test_cdt_alpha_if(hook));
	return (1);
}

int				get_ret_hook(t_e **e, char **hook)
{
	char		*var;
	char		*var2;

	if (hook[0] && hook[1] && !hook[2])
	{
		if ((var = ft_strchr(hook[1], '$')) != NULL)
			replace_var(e, &(hook[1]), ft_strdup(var + 1), 0);
		return (test_file_if(*e, hook));
	}
	else if (hook[0] && hook[1] && hook[2])
	{
		if ((var = ft_strchr(hook[0], '$')) != NULL)
			replace_var(e, &(hook[0]), ft_strdup(var + 1), 0);
		if ((var2 = ft_strchr(hook[2], '$')) != NULL)
			replace_var(e, &(hook[2]), ft_strdup(var + 1), 0);
		return (test_cdt_if(hook));
	}
	return (0);
}

int				do_while_in_if(t_e **e, char **tmp, int max, char **arg)
{
	int			ctrl;
	int			i;

	i = 0;
	while (tmp[i])
	{
		if (check_elif(tmp + i))
			return (0);
		if ((ctrl = is_script(tmp + i)) > 0)
		{
			do_shell_script(e, ft_cpy_tab(arg + i + 1), ctrl);
			i = find_correspondant(arg, 0, IF);
			if (i >= max)
				break ;
		}
		else
			*e = ft_exec_cmd(tmp[i], *e, -1);
		i++;
	}
	return (1);
}
