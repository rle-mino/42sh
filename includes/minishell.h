/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubard <jaubard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:54:02 by jaubard           #+#    #+#             */
/*   Updated: 2016/06/20 14:53:39 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define FOR 1
# define WHILE 2
# define UNTIL 3
# define CASE 4
# define IF 5
# define AND 6
# define OR 7

# define DEBUG 1

# include "edit_line.h"
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>

enum
{
	BAD_FD = -1,
	PARSE_ERROR = -2,
	NEED_FILENAME = -3,
	AMBIGUOUS_REDIR = -4,
	OPEN_ERROR = -5,
	IS_NOT_VALID = -6
};

enum
{
	RET,
	RES
};

struct sigaction sigchld_action;

typedef struct		s_export
{
	int				status;
	char			*export_env;
	bool			display;
	struct s_export	*next;
}					t_export;

typedef struct		s_e
{
	char			*err;
	char			*str;
	struct s_e		*next;
	struct s_export	*export;
	int				ret;
	int				op;
	int				status;
	int				gitlen;
}					t_e;

typedef struct		s_i
{
	char			*input;
	struct s_i		*next;
	char			n;
}					t_i;

typedef struct		s_valid
{
	char			**t;
	int				*hd;
}					t_valid;

typedef struct		s_word
{
	char			*word;
	struct s_word	*next;
}					t_word;

int					check_back_quote(char *s);
void				helper_back_quote(int fd[2], t_e *e, char *cmd);

char				*delete_subshell(char *cmd, int begin);
t_e					*ft_envdup(t_e *e);
void				reset_and_clear();
t_e					*do_shell_script_and_follow(t_e *env, char **arg, int ctrl);
void				sc_handler(int sig);
pid_t				get_pid(pid_t pid);
t_e					*do_in_shell_script(t_e **e, char **arg, int ctrl);

int					is_structure_boucle(char *boucle);
int					is_cdt(t_e **e, char **str);
int					check_cdt(t_e **e, char **str, int i, int ret);

int					jump_ctrl(char **arg, int jump, int ctrl);

int					get_ret_cmd(t_e **e, char *cmd);

t_e					*exec_next_script(t_e **e, char **arg);
char				**ft_cpy_tab(char **src);
int					error_missing(char *str);
int					find_correspondant(char **arg, int i, int st);

char				**create_in_until_while(char **arg, int i, int ctrl);

int					do_while_script(t_e **e, char **arg);

int					check_while(char **arg);

int					do_until_script(t_e **e, char **arg);

int					check_until(char **arg);

int					cdt_find_corr(char **str, int i);

int					check_subshell_full(char *cmd);

int					do_while_in_if(t_e **e, char **tmp, int max, char **arg);
int					do_if_fmethod(t_e **e, char **arg, int i, int ret);
int					do_in_if_fmethod(t_e **e, char **arg);
char				**get_between_dhook(char **arg, int *i);
int					get_ret_hook(t_e **e, char **hook);
int					get_op_hook(char **av, int i);
int					do_if_script(t_e **e, char **arg);
int					get_op_hook(char **av, int i);
char				**get_between_hook(t_e **e, char **arg, int *i);
char				**get_cmd_ret(t_e **e, char **arg);

int					check_method_if(t_e *e, char **arg);
int					check_then_fi(char **arg);
int					check_condition_if(char **arg, int i);
int					check_elif(char **arg);
int					check_then_fi_present(char **arg);
int					check_condition_file_if(char **arg, int i);
int					check_condition_alpha_if(char **arg, int i);
int					check_condition_num_if(char **arg, int i);
int					ft_isnum(char *str);
int					error_bracket_if(void);

int					test_cdt_num_if(char **hook);
int					test_file_if(t_e *e, char **hook);

int					max_tab(char **var, char **list);
t_e					*search_env(t_e *e, char *var);
t_e					*add_env_overwrite(t_e *e, char *s, char *var);

char				**delete_for(char **arg, int *stop);
char				**create_newtab_for(char **arg, int *begin, int *i,
										int *stop);
char				**create_var_for(char **arg);
char				**create_list_for(char **arg);
char				**clean_arg_for(char **arg);

int					check_method_for(char **arg);
int					check_do_done(char **arg);

void				do_for_first_method(t_e **e, char **arg);
int					do_for_script(t_e **e, char **arg);

int					is_script(char **arg);
int					is_structure_boucle(char *boucle);

t_e					*do_shell_script(t_e **e, char **arg, int ctrl);

int					env_err(void);

char				*ft_del_back(char *str);
int					check_subshell_more(char *s, int opt);

/*
***		GIT
*/

char				*get_git(char *pwd);
void				print_git(t_e *e);

/*
***		42SHRC
*/
t_e					*exec_shrc(t_e *e);

/*
***		NEWPIPE
*/

t_e					*ft_pipe(t_e *env, char *s, int i, int j);
int					get_ret(int ret);
void				child_handler(int sig);
int					ft_pipe_parse_error(char *s);

/*
***		SUBSHELL
*/
char				*get_subshell(char *cmd);
int					first_subshell(int a);
int					check_subshell_error(char *cmd);
int					is_subshell(char *cmd);
void				do_subshell(t_e *e, char *cmd);
t_word				*replace_subshell(char *cmd, char id);

/*
***		REDIRECTION
*/

int					redirect_to_file(char **redir, char **file);
int					word_before_redir(char *str, int i);
int					is_a_redir(char a);
void				redir_error(int err);
int					return_error_redir(int err, char **redir);
void				delete_redir(char *s, char **split);
int					redirection_out(int fd, char *filename, int append);
int					redirection_in(int fd, char *filename, int heredoc,
																int save_fd);
int					loop_redir(char *str, int save_fd);
char				*until_redir(char *file);
char				*get_name_of_redir(char *redir, int i);
int					detect_redir_out(char *redir);
int					detect_redir_in(char *redir, int save_fd);

void				malloc_handling(void);

char				*inc_var(char *var, int inc, t_e **e);
int					check_inc(char *var);
int					ft_varcmp(char *var, char *env);
void				replace_var(t_e **e, char **str, char *var, int i);
char				*get_any_env_var(t_e **e, char *var);
char				*get_any_local_var(t_e **e, char *var);

void				safe_exit(int a, char *str);
char				*get_name_prog(char *str);

char				**ft_cmdsplit_dquote(char *str);
char				**ft_cmdsplit_squote(char *str);

t_e					*ft_exec_bq(char *cmd, t_e *env);
char				*replace_space(char *str);
char				*ft_replace_back_quote(char *s, t_e *e);
void				ft_back_quote(char *s, t_e *e);

t_line				*start_edit_line(t_le *le, t_e *env);
char				*clear_str(char *str);
void				ft_env(char **t, t_e *env);
void				ft_env_args(char **t, t_e *env);
t_e					*exec_env_arg(char **t, t_e *env);
int					ft_ispath(char *s);
t_e					*ft_exec_path(t_e *env, char *s, char **t, char *tmp);
t_e					*ft_exec(t_e *env, char *s, char **arg, char *tmp);
char				**choose_your_print(char **t, char *env);
char				*ft_get_oldpwd(char *s, t_e *env);
int					ft_exit(char *s, char *cmd, char **arg, t_e *env);
t_e					*ft_change_env(t_e *env, t_e *mod, char **t, int check);
t_e					*ft_add_env(char **t, t_e *env, int check);
t_e					*ft_del_env(char *s, t_e *env);
char				*ft_get_path(t_e *env, char *s);
t_e					*ft_change_pwd(t_e *env, char *s, int i, char *new);
int					ft_print_error(char *s, char *cmd, int i);
char				**ft_go_home(char **t, t_e *home, int i);
char				*ft_go_home2(char *s, char *s2);
t_e					*call_builtins(char *s, t_e *env, int i);
t_e					*ft_get_env(int i);
t_e					*ft_exec_cmd(char *s, t_e *env, int i);
t_e					*ft_exec_cmd2(t_e *env, char *cmd, char **arg, char *s);
t_e					*ft_pipe(t_e *env, char *s, int i, int j);
t_e					*ft_exec_pipe(char *str, t_e *env);
void				ft_prompt(t_e *env);
void				print_username(t_e *env);
void				print_cwd(t_e *env);
int					ft_countarg(char *s);
int					ft_nopelol(char *s);
t_e					*lol_error(char *end, char *no_redir, t_e *env, char *cmd);
t_e					*ft_another_error(char *s, t_e *env);
char				*ft_get_argstr(char **t);
int					double_red(char *s, char c);
int					check_redir(char *s);
t_e					*ft_redir_loop(t_e *e, char *s);
t_e					*ft_redir(t_e *env, char *s, char *no_redir);
t_e					*ft_redir2(t_e *env, char *s, char *no_redir, char *arg);
t_e					*ft_exec_redir(int fd, t_e *env, char *s, char *no_redir);
t_e					*ft_redir_err(t_e *env, char *s, char *file);
t_e					*ft_llredir(char *end, t_e *env, char *no_redir);
char				*cmd_llredir(char *s);
int					red_error(t_e *env, char *s, int i);
char				*print_llredir(char *end, char *line);
t_e					*ft_gettmp(t_e *env, char **t);
void				ft_deltmp(t_e *env);
t_e					*ft_add_e(t_e *env, char *s);
char				**switch_env(t_e *env);
char				*go_homu(char *s1, char *s2);
t_e					*norme_got_me(t_e *env, char *s, int check, char *free_lol);
int					is_empty(char *s);
void				sig_handler(int signo);
int					check_empty(char *s, int i, int j);
t_e					*set_shlvl(t_e *env);
int					*get_redir_fd(char *s, int fd, int i, int *redir);
void				ft_close_red(int *redir, int fd);
char				*cmd_redirless(char *s, int i);
int					ft_err_red(t_e *env, char *s, int i);
int					check_pfd(char *s);
int					check_r(char *s);
int					fuck_la_norme(char *s);
int					*get_special_fd(char *s, int *file);
int					central_fiction(char **t);
int					clear_pipe(char **t, int i);
void				print_pipe(char *s, char *print, int i, int check);
char				*final_flash(char *s);
void				ft_clean_exit(int i, char *cmd, char **arg, t_e *env);
t_i					*get_input(t_i *inp, int *hd, char **cpy, t_e *e);
t_i					*ft_add_input(t_i *inp, char *s);
void				ft_del_input(t_i *inp, char *cpy);
char				*current_input(t_i *inp);
int					init_input(void);
int					end_input(void);
int					input_num(t_i *inp);
int					ft_xmove(int cursor, char *s, char d);
int					*ft_ymove(char **input, int *hd, t_i *inp, char d);
t_i					*ret_input(char **t, int ind, t_i *inp, char c);
char				**input_tab(t_i *inp, int l);
t_valid				*init_valid(t_i *inp);
void				get_salty(int i, char **s1, char **s2);
t_valid				*ft_vprompt(int i, t_valid *v, char c);
void				del_v(t_valid *v, int *hd);
int					*hist_data(t_i *inp);
void				xmove_line(int *old_c, int *new_c, char d);
int					*arrow_jump(int *hd, int arrow, char **input);
int					*cursor_position(int i);
void				ft_clear(t_e *e, int cursor, char *s, int ctrl);
char				*ft_copy(char *cpy, char *cmd);
char				*ft_paste(char *cmd, char *cpy, int cursor);
char				*update_input(char *s, char c, int cursor);
int					fd_loop(char *s);
int					end_read(char c, int i, char *s);
int					ret_err(char **t);
int					ret_ok(char **t);
t_e					*ret_err_redir(t_e *env);
t_e					*close_red(char *s, int *red, int fd, t_e *env);
t_e					*clean_red(char *s, char **t, t_e *env);
void				free_exec(char *s, char **t, char *s2, char **t2);
int					cmd_row(char *old, char *new, int o, int n);
void				save_cursor_update(char *s, int l);
void				restore_position(char *s, int pos);
t_e					*ft_logical_operator(char *s, t_e *env, int n);
char				next_operator(char *s);
int					count_op(char *s);
int					init_term(void);
int					reset_term(void);
t_e					*ft_cd(char **t, t_e *env, int i, char *str);
int					ft_echo(char **args, int status);
t_e					*get_t_env(t_e *e);
void				update_size(int sig);
void				stop_heredoc(int sig);
void				restart_prompt(int sig);
t_le				*prepare_term(void);
int					ft_history(char **t);
char				**ft_inhib(char *s, t_e **e);
t_e					*ret_env_err(t_e *e, int status);
char				*cmd_redirless2(char *s);
char				*cmd_redirless3(char *ret, char *s, int i);
int					*ret_redir_fd(int *redir);
int					*ret_special_fd(int *file, char *s, int i);
t_e					*ft_setenv(char **t, t_e *env, int i, int check);
t_e					*ft_unsetenv(char **t, t_e *env, int i);
t_e					*ft_unsetenv_error(char **t, t_e *env);
t_e					*ft_init_env(void);
int					read_error(char *s);
t_e					*ft_help_read(t_e *env, char *s, char *inp, char *tmp);
t_e					*empty_export(t_e *e, int i, int nw, char **word);
void				ft_builtin_clear(void);

/*
*** EXPORT AND UNSET HERE
*/

/*
*** TEMP
*/
t_e					*ft_merge_env(t_e *e, char *key, char *v);
t_export			*ft_export_temp(char **t, char *cmd, t_export *env, t_e *e);
t_export			*ft_export_temp2(t_export *env, char *s);

/*
*** GET
*/

t_export			*ft_get_export(int i);
t_export			*ft_add_export(t_export *env, char *s, bool b);
t_export			*get_t_export(t_export *e);
t_export			*set_shlvl_export(t_export *env);

/*
*** SET
*/

t_e					*ft_setexport(char **t, t_e *env, int i, int check);
t_e					*ft_setexport_err(t_e *env);
t_e					*ft_setexport2(t_e *env, t_export **temp, char *key);
t_e					*ft_change_export(t_e *env, char **t,
		t_export **temp, int check);
t_e					*ft_add_export_second(char **t, int check, t_e *e);

/*
*** UNSET
*/

t_export			*ft_unset(char **t, t_export *env, int i, t_e *e);
void				ft_unset_first(char **t, t_export *env);
void				ft_unset_second(char **t, t_export *temp);
t_export			*ft_del_export(char *s, t_export *env);

/*
*** DISPLAY
*/

void				ft_export(char **t, t_export *env, int status);

t_e					*read_export(char *s, char *s2, t_e *e);
t_e					*ft_read(char *cmd, t_e *e);
t_e					*ft_read2(char **word, char **input, char *line, t_e *e);
int					check_read_flags(char *s);
char				*last_word(char *s, int nw);
t_e					*read_no_flags(char *cmd, t_e *e);
int					clean_read(char **t, char **t2, char *s, int i);
t_e					*export_env(t_e *e, char *key, char *val);

/*
***	LIST FILES
*/
t_word				*get_files(char *path);
int					get_files_recu(t_word *folder);
char				*get_name(char *path, char *new_name);
void				push_front(char *new_name, t_word *word);
void				pushback(char *new_name, t_word **word);
void				push_in_file(struct dirent *file, t_word **word);
char				**get_path_and_word(char *str);

/*
***	GLOB
*/
char				*ft_glob(char *line);
int					ne_glob(char *split);
int					match(char *a, char *b);
int					is_glob_char(char c);
void				add_to_poss(char *poss, int *i, char a, char b);
char				*poss_in_bra(char *a, int *i);
char				*merge_word(t_word *words, char *path);
char				*merge_split(char **split);
void				follow_match(char *b, int *j, char **split, int k);
int					check_match(char **split, char *b, int *j, int k);
void				glob_add_word(char **new_split, char *path, t_word *words);

/*
*** EXTRA
*/

void				ft_builtin_reset();

#endif
