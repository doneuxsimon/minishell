
char	**big_free(char **str, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(str[j]);
	free(str);
	return (NULL);
}

char	**ft_str_big_dup(char **str)
{
	char	**new;
	int		len_w;
	int		len_l;
	int		i;
	int		j;

	i = -1;
	len_w = len2(str);
	new = (char **)malloc(sizeof(char *) * (len_w + 1));
	if (!new)
		return (NULL);
	while(++i < len_w)
	{
		j = -1;
		len_l = len1(str[i]);
		new[i] = (char *)malloc(sizeof(char) * (len_l + 1));
		if (!new[i])
			return (big_free(new, i));
		while(++j < len_l)
			new[i][j] = str[i][j];
		new[i][j] = 0;
	}
	new[i] = 0;
	return (new);
}
