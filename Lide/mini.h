/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:03:36 by lide              #+#    #+#             */
/*   Updated: 2022/06/09 18:47:01 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../Sdoneux/test.c"

typedef struct s_line
{
	char	*ft;
	char	*opt;
	char	*arg;
	char	*file;
	t_line	*next;
	t_line	*before;
}				t_line;

char	**big_split(char const *s, char *c);
int		in_tab(char str, char *c);
int		ft_pass(char const *s, char *c, int i);

#endif
