void	print_env(void)
{
	while (g_var->before != NULL)
		g_var = g_var->before;
	while (g_var->next != NULL)
	{
		printf("name = %s| value = %s\n", g_var->name, g_var->value);
		g_var = g_var->next;
	}
	printf("name = %s| value = %s\n", g_var->name, g_var->value);
}

void	print_cmd(t_list **cmd)
{
	int	i;

	while ((*cmd)->before != NULL)
		*cmd = (*cmd)->before;
	while ((*cmd)->next != NULL)
	{
		printf("%s / %s /", (*cmd)->ft, (*cmd)->opt);
		i = -1;
		if ((*cmd)->arg != NULL)
			while ((*cmd)->arg[++i])
				printf("%s /", (*cmd)->arg[i]);
		printf("%s / %s / %d / %d / %d\n", (*cmd)->link, (*cmd)->tmp, (*cmd)->infile, (*cmd)->outfile, (*cmd)->pos);
		*cmd = (*cmd)->next;
	}
	printf("%s / %s /", (*cmd)->ft, (*cmd)->opt);
	i = -1;
	if ((*cmd)->arg != NULL)
		while ((*cmd)->arg[++i])
			printf("%s /", (*cmd)->arg[i]);
	printf("%s / %s / %d / %d / %d\n", (*cmd)->link, (*cmd)->tmp, (*cmd)->infile, (*cmd)->outfile, (*cmd)->pos);
	free_all(cmd);
}

	// while (++i < len)
	// 	printf("%s\n", str[i]);
