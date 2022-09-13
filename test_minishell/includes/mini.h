/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoneux <sdoneux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:03:36 by lide              #+#    #+#             */
/*   Updated: 2022/09/13 15:39:31 by sdoneux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <curses.h>
# include <term.h>

# define ERROR1 "redirection: syntax error near unexpected token `newline'"
# define ERROR2 "minishell: warning: here-document at line %d"
# define ERROR2BIS " delimited by end-of-file (wanted `%s')"
# define ERROR_EXPORT "minishell: export: `%s': not a valid identifier\n"

typedef struct s_var
{
	int				error;
	char			*name;
	char			*value;
	int				*returned;
	int				*pid;
	struct s_var	*next;
	struct s_var	*before;
}					t_var;

typedef struct s_list
{
	char			*ft;
	char			*opt;
	char			**arg;
	char			*link;
	char			*tmp;
	int				infile;
	int				outfile;
	int				pos;
	int				ct_line;
	struct s_list	*next;
	struct s_list	*before;
}					t_list;

typedef struct s_exec
{
	char	**cmd_path;
	char	**envp;
	char	*cmd;
	char	**cmd_args;
}			t_exec;

typedef struct s_exec_pipe
{
	char	**cmd_path;
	int		pid[4];
	int		piped1[2];
	int		piped2[2];
	int		count;
	char	**envp;
}			t_exec_pipe;

t_var	*g_var;

char	*ft_strdup(char *s1);
int		ft_strncmp(char *s1, char *s2, int n);
t_var	*init_var(t_var *var);
t_list	*init_lst(t_list *cmd, int line);
char	*ft_itoa(int n);
char	**mini_split(char *line);
int		check_expt(char c, int verif);
int		skip_word(char *line, int i);
int		skip_separator(char *line, int i);
int		skip_space(char *line, int *i);
void	*free_split(char **str, int max);
char	*free_env(char *str, char *ret, char *env);
char	**check_dol(char **str, int len);
int		len1(char *str);
int		ft_export(char **str, int i, int len);
int		len2(char **str);
int		put_in_struct(char **str, t_list **cmd);
int		redirection(char **str, t_list **cmd, int len);
int		cmp_line(char *str, char *line);
char	*find_name(t_list **cmd);
void	remove_g_var(void);
int		remove_quote(char **str, int i);
int		ft_unset(char **str, int i, int len);
int		check_g_var(char *str);
void	free_envp(void);
char	*free_char(char *str, char *print);
int		free_redirection(char **str, t_list **cmd, int len);
void	free_all(t_list **cmd, int verif);
int		skip_s_quote(char **str, int i, int j);
char	*cp_name(char *str, int *len, int tmp, int *j);
char	*cp_value(char *value, char *line, int *len);
char	*print_str_perror(char *str);
int		print_perror(char *str);
int		print_error(char *str);
int		find_infile(char **str, t_list **cmd, int *i, int fd);
int		remove_red_quote(char **str, int i);
int		put_pipe(t_list **cmd, char **str, int i);
int		put_ft_and_opt(char **str, t_list **cmd, int *i);
int		put_arg(char **str, t_list **cmd, int len, int *i);
void	sig(int i);
int		free_infile(char **str, int *i);
void	skip_sep_error(int ct, int sep);
int		check_minus(char **str, int *i);
char	**g_var_to_char(void);
int		*init_returned(void);
char	**get_line(char *line);
int		ft_strncmp_2(char *s1, char *s2, int n);
void	ft_end(t_list **stack);
void	ft_begin(t_list **stack);
void	ft_end_var(t_var **stack);
void	ft_begin_var(t_var **stack);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strjoin_2(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		verify_builtins(t_list *list, char **envp);
void	ft_start_exec(t_list *list, char *path, char **envp);
char	*get_cmd2(char **cmd_paths, char *cmd, t_list *list);
void	ft_exec_pipes(t_list *list, char **cmd_path, char **envp, int count);
void	ft_fork_0(t_list *list, t_exec_pipe *exec);
void	ft_fork_1(t_list **list, t_exec_pipe *exec);
void	ft_fork_2(t_list *list, t_exec_pipe *exec);
void	ft_fork_3(t_list *list, t_exec_pipe *exec);
void	ft_close_wait(int *piped1, int *piped2, int *pid, int i);
void	ft_exec(t_list *list, char **cmd_path, char **envp);
void	ft_exec_nothing(t_list *list, t_exec *exec);
int		ft_count_dup(t_list *list, int i);
t_exec	*ft_init_exec(char **cmd_path, char **envp);
void	ft_pwd(void);
void	ft_echo(t_list *list);
void	ft_env(int *i);
void	ft_exit(t_list *cmd);
int		ft_compare_n(char *opt);
int		ft_count_forks(t_list *list);
void	ft_exec_arg_opt(t_list *list, t_exec *exec, int i);
void	ft_exec_arg(t_list *list, t_exec *exec, int i);
void	ft_exec_opt(t_list *list, t_exec *exec);
int		ft_exit_pipe(void);
int		ft_exit_fork(void);
void	ft_freed(char **cmd_path);
int		ft_skip_n(t_list *list, int i, int n);
int		ft_compare_n2(t_list *list);
int		dup0(t_list *list, int piped);
int		dup1(t_list *list, int piped);
void	check_in_outfile(t_list *list);
void	ft_cat_return(t_list *list, int pid);
void	ft_close_pipe(t_exec_pipe *exec);
int		change_question_error(char **str, char *nb, int i, int verif);
int		command_exist(t_list *list, char **cmd_path);
int		verif_builtin(t_list *list);
void	ft_cd(t_list *list);
void	ft_unset_old(void);
void	ft_export_2(void);
void	*free_join(char **str, int i);
void	ft_modify_env(void);
int		is_digitt(char *arg);
int		ft_exit_malloc(void);
char	*verif_line(char *line, t_list *cmd);
char	**realloc_str(char **str, char **line, int *i);
void	ft_print_delete(t_var **var);
int		check_w_sp(char *str, int j);
int		error_init_returned(int verif);
char	*get_cmd_utils(char **cmd_paths, char *cmd);
void	ft_cd_utils(void);
int		ft_exit_close(void);
void	ft_exit_utils(t_list *cmd);
void	ft_cd_utils_minus(void);
int		ft_exit_cd(void);
void	ft_cd_utils2(char *tmp);
char	*get_cmd2_utils(char **cmd_paths, char *cmd);
int		check_pipe(char *line);
char	**print_pipe_error(char *line);
void	check_in_outfile2(t_list *list);

#endif
