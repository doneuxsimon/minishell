#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*path;
	char	*tmp;
	int		i;

	if (argc != 1)
		exit(EXIT_SUCCESS);
	if (strncmp(argv[0], "./Minishell", 7) != 0)
		exit(EXIT_SUCCESS);
	path = getenv( "PATH" );
	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		i = verify_builtins(line, envp);
		tmp = get_cmd(path, line);
		//printf("%s\n", tmp);
	}
	return (0);
}
