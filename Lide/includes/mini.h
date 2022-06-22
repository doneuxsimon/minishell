/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:03:36 by lide              #+#    #+#             */
/*   Updated: 2022/06/22 05:31:33 by lide             ###   ########.fr       */
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
// # include "../wraloc.h"


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
	char			*arg;
	char			*link;
	char			*tmp;
	int				infile;
	int				outfile;
	int				pos;
	struct s_list	*next;
	struct s_list	*before;
}					t_list;

t_var	*g_var;

void	init_var(t_var **var);
char	*ft_itoa(int n);
t_list	*init_lst(t_list *cmd);
char	**mini_split(char *line);
int		check_expt(char c, int verif);
int		skip_word(char *line, int i);
int		skip_separator(char *line, int i);
int		skip_space(char *line, int *i);
void	*free_split(char **str, int max);
char	*free_env(char *str, char *ret);
char	*unchange_env(char *str, int *j, int len);
char	**check_env(char **str);
int		len1(char *str);
int		len2(char **str);
void	put_in_struct(char **str,t_list **cmd, t_var **var);
void	redirection(char **str, t_list **cmd, int len);
int		cmp_line(char *str, char *line);
char	*find_name(t_list **cmd);

#endif
