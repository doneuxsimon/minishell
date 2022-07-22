#ifndef TEST_H
# define TEST_H

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
	char			*tmp;
	char			*link;
	int				piped[2];
	int				pos;
	int				infile;
	int				outfile;
	struct s_list	*next;
	struct s_list	*before;
}					t_list;

t_var	*g_var;

void	ft_end(t_list **stack);
void	ft_begin(t_list **stack);
char	*find_path(char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*get_cmd(char *path, char *cmd);
int		verify_builtins(char *line, char **envp);
void	ft_start_exec(t_list *list, char *path, char **envp);

#endif
