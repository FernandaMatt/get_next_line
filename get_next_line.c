/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:41:50 by fcaetano          #+#    #+#             */
/*   Updated: 2022/06/15 15:23:38 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* size_t	ft_strlen(const char *str)
{
	size_t	n;

	if (!str)
		return (0);
	n = 0;
	while (str[n])
		n++;
	return (n);
}

char	*ft_strdup(char *src)
{
	char	*ret;
	int	c;

	c = ft_strlen(src) + 1;
	ret = malloc(c * sizeof(*ret));
	if (!ret)
		return (ret);
	c = 0;
	while (src[c])
	{
		ret[c] = src[c];
		c++;
	}
	ret[c] = 0;
	return (ret);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize == 0)
		return (ft_strlen((char *)src));
	while (src[i] && i < destsize - 1 && i != destsize)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (ft_strlen((char *)src));
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	newstr = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!newstr)
		return (newstr);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstr + ft_strlen(s1), s2, ft_strlen((char *)s2) + 1);
	free(s1);
	free(s2);
	return (newstr);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return (i);
		i++;
	}
	if ((char)c == s[i])
		return (i);
	return (-1);
} */

char	*ft_read(int fd)
{
	int		bread;
	char	*readbuf;

	readbuf = malloc(BUFFER_SIZE + 1 * sizeof(*readbuf));
	if (!readbuf)
		return (readbuf);
	bread = read(fd, readbuf, BUFFER_SIZE);
	if (bread == 0)
	{
		free(readbuf);
		return (ft_strdup(""));
	}
	readbuf[bread] = 0;
	if (bread < 0)
	{
		free(readbuf);
		return (0);
	}
	else
		return (readbuf);
}

char	*check_bread(char *sbuf, char *line, int nli)
{
	char	*temp;

	if (!sbuf)
		return (0);
	nli = ft_strchr(sbuf, '\n');
	ft_strlcpy(line, sbuf, nli + 2);
	temp = sbuf;
	sbuf = ft_strdup(sbuf + nli + 1);
	if (temp)
		free(temp);
	return (sbuf);
}

char	*check_EOF(char *sbuf,char *temp)
{
	if (temp == 0)
	{
		if (sbuf)
			free(sbuf);
		return (0);
	}
	if (ft_strlen(sbuf) > 0)
	{
		free(temp);
		return (sbuf);
	}
	free(temp);
	free(sbuf);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*sbuf;
	char		*line;
	int			nli;

	if (fd < 0)
		return (0);
	while (1)
	{
		nli = ft_strchr(sbuf, '\n');
		if (nli >= 0)
		{
			line = malloc((nli + 2) * sizeof(*line));
			sbuf = check_bread(sbuf, line, nli);
			return (line);
		}
		line = ft_read(fd);
		if (ft_strlen(line) == 0)
		{
			line = check_EOF(sbuf, line);
			sbuf = 0;
			return (line);
		}
		sbuf = ft_strjoin(sbuf, line);
	}
}

/* int main(void)
{
	int 	fd;
	char	*line;

	fd = open("test.txt", 0);
	
	line = get_next_line(fd);
	while (line)
	{	
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
} */
