#include "../includes/test.h"

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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*path;
	char	*tmp;
	int		i;
	t_list	*list;

	if (argc != 1)
		exit(EXIT_SUCCESS);
	if (strncmp(argv[0], "./Minishell", 7) != 0)
		exit(EXIT_SUCCESS);
	list = malloc(sizeof(t_list));
	ft_initialise(&list);
	path = getenv( "PATH" );
	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		i = verify_builtins(line, envp);
		tmp = get_cmd(path, line);
		if (i == 0)
		{
			list->ft = "wc";
			list->opt = "-w";
			list->arg = "bonjour";
			list->outfile = open("open.txt",  O_TRUNC | O_CREAT | O_RDWR, 0000644);
			ft_start_exec(list, path, envp);
			//printf("%i\n", unlink(".tmp"));
		}
		//printf("%s\n", tmp);
	}
	return (0);
}
