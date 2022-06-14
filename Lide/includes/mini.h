/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:03:36 by lide              #+#    #+#             */
/*   Updated: 2022/06/14 16:08:10 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../../Sdoneux/test.h"
# include <signal.h>

typedef struct s_list
{
	char			*ft;
	char			*opt;
	char			*arg;
	char			**var;
	char			**exp;
	char			*file;
	char			*link;
	int				pos;
	struct s_list	*next;
	struct s_list	*before;
}				t_list;

	char	**var;

char	**mini_split(char *line);
int		check_expt(char c, int verif);
int		skip_word(char *line, int i);
int		skip_separator(char *line, int i);
int		skip_space(char *line, int *i);

#endif
