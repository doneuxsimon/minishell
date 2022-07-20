/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:03:36 by lide              #+#    #+#             */
/*   Updated: 2022/07/20 15:43:21 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../wraloc.h"

typedef struct s_var
{
	char			*name;
	char			*value;
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
	struct s_list	*next;
	struct s_list	*before;
}					t_list;

t_var	*g_var;

char	*ft_strdup(char *s1);
int		ft_strncmp(char *s1, char *s2, int n);
t_var	*init_var(t_var *var);
t_list	*init_lst(t_list *cmd);
char	*ft_itoa(int n);
char	**mini_split(char *line);
int		check_expt(char c, int verif);
int		skip_word(char *line, int i);
int		skip_separator(char *line, int i);
int		skip_space(char *line, int *i);
void	*free_split(char **str, int max);
char	*free_env(char *str, char *ret, char *env);
char	**check_dol(char **str);
int		len1(char *str);
int		ft_export(char **str, int *i, int len/*, char **env*/);
int		len2(char **str);
int		put_in_struct(char **str, t_list **cmd/*, char **env*/);
int	redirection(char **str, t_list **cmd, int len);
int		cmp_line(char *str, char *line);
char	*find_name(t_list **cmd);
void	remove_g_var(void);
int		remove_quote(char **str, int i);
int		ft_unset(char **str, int *i, int len/*, char **env*/);
int		check_g_var(char *str);
// int		check_equal(char **str, int len/*, char **env*/);
void	free_envp(void);
void	free_all(t_list **cmd);
char	**ft_str_big_dup(char **str);

#endif
