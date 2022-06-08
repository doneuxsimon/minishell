#include "test.h"

int	main(void)
{
	char	*line;
	char	*path;
	char	*tmp;

	path = getenv( "PATH" );
	while (1)
	{
		line = readline("Minishell $> ");
		add_history(line);
		tmp = get_cmd(path, line);
		printf("%s\n", tmp);
	}
	return (0);
}
//echo