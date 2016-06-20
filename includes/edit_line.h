/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 18:57:41 by rle-mino          #+#    #+#             */
/*   Updated: 2016/06/16 17:37:09 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_LINE_H
# define EDIT_LINE_H

# include "libft.h"

typedef struct			s_line_edit
{
	struct s_line_edit	*next;
	struct s_line_edit	*prev;
	int					x;
	int					y;
	int					is_orig;
	char				c;
	int					paired;
}						t_line;

typedef struct			s_hist
{
	t_line				*old_line;
	int					len;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

typedef struct			s_le
{
	int					fd;
	int					w_sizex;
	int					w_sizey;
	int					pos_x;
	int					pos_y;
	int					sig;
	t_line				*line;
	char				*prompt;
}						t_le;

typedef struct			s_noeud
{
	unsigned char		lettre;
	struct s_noeud		*filsg;
	struct s_noeud		*frered;
}						t_arbre;

enum
{
	READ_HIST,
	WRITE_HIST,
	NEXT_HIST,
	PREV_HIST,
	FIRST_HIST,
	SECOND_HIST,
	ADD_HIST,
	SAVE_LINE,
	RES_ORI,
	GET_HIST
};

enum
{
	LEFT = 1,
	UP,
	DOWN,
	RIGHT
};

enum
{
	ADD_SPACE,
	RUP_FOR_HIST
};

enum
{
	PAIRING,
	HEREDOC,
	NORMAL
};

/*
***		display
*/

void					add_to_line_display(t_le *le, t_line **line);
void					delete_char_display(t_line **line, t_le *le);
void					redisplay_line(t_line *line, t_le *le);
int						redisplay_line_index(t_line *line, t_le *le);
/*
***		back
*/
t_line					*add_space_between_redir(t_line *line);
void					update_size(int sig);
void					add_word_to_line(char *to_add, t_le *le);
void					restart_prompt(int sig);
void					stop_heredoc(int sig);
void					show_me_cursor(t_le *le);
t_line					*edit_line(t_le *le);
int						ft_is_arrow(char *buffer);
int						ft_is_del_or_back(char *buffer);
void					get_pos_cursor(int *x, int *y);
int						linelen(t_line *line);
char					*to_string(t_line *line, int space);
int						ft_putint(int c);
void					add_to_line(t_le *le, t_line **line, char n);
t_line					*get_last_line(t_line *line);
t_line					*get_first_line(t_line *line);
void					clipboard_to_line(char *first_chars, t_le *le);
void					parse_buffer(char *buffer, t_le *le, int mode);
void					delete_char(t_le *le, t_line **line, char c);
int						get_fd(int fd);
t_le					*get_t_le(t_le *le);
int						is_a_unescaped_quote(t_line *line);
/*
***		move
*/
void					move_to_first(t_le *le, t_line **line);
void					move_to_last(t_le *le, t_line **line);
void					move_left(t_le *le, t_line **line);
void					move_right(t_le *le, t_line **line);
void					move_to_word(int dir, t_le *le);
void					move_vertically(int dir, t_le *le);
void					move_to_extrem(int dir, t_le *le);
void					move_cursor(t_le *le, int dir, t_line **line, int mode);
/*
***		pairs, pipe, heredoc
*/
char					*missing_pair(t_line *line, int *quotes);
char					reverse_pair(char c);
int						search_pair(t_line *line, char f);
int						is_not_paired(int *inquotes, int *paired, t_line *line);
void					check_quotes(t_line *line, int *indquote);
int						is_paired(int *inquotes, char *find, int paired,
																t_line *line);
int						is_in_quotes(int *quotes, t_line *line);
void					edit_line_pairing(t_le *le, char *prompt);
t_line					*get_orig_line(t_line *line);
t_line					*edit_line_heredoc(t_le *le, char *end, int bsn);
void					prepare_heredoc(t_le *le, t_line *line);
void					ignore_heredoc(t_le *le, void *tmp);
int						end_is_not_in_line(t_le *le, char *end);
/*
***		history
*/
void					*history(int query, t_line *line);
void					*clear_hist(t_hist *hist);
t_hist					*generate_hist(t_line *cmd, t_hist *next, t_hist *prev);
t_line					*to_line(char *cmd);
t_line					*cpy_line(t_line *line);
void					clear_line(t_line *line);
int						get_hist_fd(void);
t_hist					*get_first_hist(t_hist *hist);
t_hist					*get_last_hist(t_hist *hist);
void					create_new_hist(t_hist **history, t_line *line);
t_line					*cut_line_for_hist(t_line *line);
int						dina_hist(t_le *le, char *buffer);
int						add_hist_to_line(t_le *le, char *buffer);
/*
***		completion
*/
void					complete_word(t_line **line, t_le *le);
void					advanced_completion(t_le *le, char **path_and_word);
void					display_poss(void *poss, int *pos_y, int selected,
																	t_le *le);
char					*parse_buffer_completion(char *buffer, int *selected,
																void *word);
size_t					nb_word(void *word);
int						files_per_lines(void *word);
void					clear_words(void *word);
size_t					get_max_len(void *word);
char					*selected_word(void *data, int selected);
char					*delete_useless_char(char *a, char *b);
void					free_autocomplete(t_arbre *tmp, char *buffer,
														char **path_and_word);
int						too_many_or_less_poss(void *word, t_le *le);

#endif
