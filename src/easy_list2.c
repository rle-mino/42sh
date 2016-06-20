/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 15:13:13 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/19 17:58:00 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "minishell.h"

void	push_in_file(struct dirent *file, t_word **word)
{
	if (file && *word &&
		ft_strcmp(file->d_name, (*word)->word) < 0 && file->d_name[0] != '.')
		pushback(file->d_name, word);
	else if (file && file->d_name[0] != '.')
		push_front(file->d_name, *word);
}

void	clear_words(void *word)
{
	t_word	*tmp;
	t_word	*to_delete;

	to_delete = word;
	while (to_delete)
	{
		tmp = to_delete;
		to_delete = to_delete->next;
		free(tmp->word);
		free(tmp);
	}
}

void	push_front(char *new_name, t_word *word)
{
	t_word		*new;

	new = ft_memalloc(sizeof(t_word));
	new->word = ft_strdup(new_name);
	while (word && word->next)
	{
		if (ft_strcmp(word->next->word, new_name) >= 0)
		{
			new->next = word->next;
			word->next = new;
			return ;
		}
		word = word->next;
	}
	word->next = new;
}

void	pushback(char *new_name, t_word **word)
{
	t_word	*new;

	new = ft_memalloc(sizeof(t_word));
	new->next = *word;
	*word = new;
	new->word = ft_strdup(new_name);
}
