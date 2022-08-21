#include "../includes/mini.h"

void	ft_initialise(t_list **list)
{
	(*list)->arg = NULL;
	(*list)->opt = NULL;
	(*list)->ft = NULL;
	(*list)->outfile = 0;
	(*list)->pos = 0;
	// (*list)->var = NULL;
	// (*list)->exp = NULL;
	(*list)->link = NULL;
	(*list)->next = NULL;
	(*list)->before = NULL;
}