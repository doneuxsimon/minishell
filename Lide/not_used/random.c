
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


int	ct_char(char *str)
{
	int		j;
	int		len;
	char	quote;

	j = -1;
	len = 0;
	quote = '\0';
	while (str[++j])
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			quote = str[j];
			while (str[++j] != quote)
				len++;
		}
		else
			len++;
	}
	if (!quote)
		return (-1);
	return (len);
}

char	*remove_unwanted_quote(char **str, int i, int ct)
{
	int		j;
	int		x;
	char	quote;
	char	*tmp;

	j = -1;
	x = 0;
	tmp = (char *)malloc(sizeof(char) * (ct + 1));
	if (!tmp)
		return (NULL);
	while (str[i][++j])
	{
		if (str[i][j] == '\'' || str[i][j] == '\"')
		{
			quote = str[i][j];
			while (str[i][++j] != quote)
				tmp[x++] = str[i][j];
		}
		else
			tmp[x++] = str[i][j];
	}
	tmp[x] = '\0';
	return (tmp);
}

int	remove_quote(char **str)
{
	int		i;
	int		ct;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		ct = ct_char(str[i]);
		if (ct != -1)
		{
			tmp = remove_unwanted_quote(str, i, ct);
			if (!tmp)
			{
				printf("hello\n");
				return (0);
			}
			free(str[i]);
			str[i] = tmp;
		}
	}
	return (1);
}
