/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:03:36 by lide              #+#    #+#             */
/*   Updated: 2022/06/10 20:14:13 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../../Sdoneux/test.h"

typedef struct s_list
{
	char	*ft;
	char	*opt;
	char	*arg;
	char	*file;
	struct s_list	*next;
	struct s_list	*before;
}				t_list;

char	**big_split(char const *s, char *c);
int		in_tab(char str, char *c);
int		ft_pass(char const *s, char *c, int i);
char	**mini_split(char *line);
int		nb_word(char *line);
void	skip_word(char *line, int *i);
void	*free_split(char **str, int max);

#endif
