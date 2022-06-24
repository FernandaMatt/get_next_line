#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(const char *str)
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

/* char    *ft_substr(char const *s, unsigned int start, size_t len)
{
	char    *substr;

	if (start >= ft_strlen(s))
		return(ft_strdup(""));
	substr = malloc((len+1)*sizeof(*s));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, &s[start], len+1);
	return (substr);
} */

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	char	*temp;

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
}

char	*ft_read(int fd)
{
	int		bread;
	char	*readbuf;

	readbuf = malloc(BUFFER_SIZE + 1 * sizeof(*readbuf));
	if (!readbuf)
		return (readbuf);
	bread = read(fd, readbuf, BUFFER_SIZE);
	readbuf[bread] = 0;
	if (bread == 0)
	{
		free(readbuf);
		return (ft_strdup(""));
	}
	if (bread < 0)
	{
		free(readbuf);
		return (0);
	}
	else
		return (readbuf);
}

char	*ft_checkbread(char *sbuf, char *line)
{
	int		nli;
	char	*temp;

	if (!sbuf)
		return (0);
	nli = ft_strchr(sbuf, '\n');
	if (nli < 0) //do i needd this line?
		return (0); //do i needd this line?
	else //do i needd this line?
	{
		ft_strlcpy(line, sbuf, nli + 2);
		temp = sbuf;
		sbuf = ft_strdup(sbuf + nli + 1);
		if (temp)
			free(temp);
		return (sbuf);
	}
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
	char		*temp;
	char		*line;

	while (1)
	{
		if (ft_strchr(sbuf, '\n') > 0)
		{
			line = malloc((ft_strchr(sbuf, '\n') + 2) * sizeof(*line));
			sbuf = ft_checkbread(sbuf, line);
			return (line);
		}
		temp = ft_read(fd);
		if (ft_strlen(temp) == 0)
		{
			line = check_EOF(sbuf, temp);
			sbuf = 0;
			return (line);
		}
/* 		if (temp == 0 || ft_strlen(temp) == 0)
		{
			sbuf = ft_strjoin(sbuf, temp);
			if	(ft_strlen(sbuf) > 0)
				return (sbuf);
			free(sbuf);
			return (0);
		} */
		sbuf = ft_strjoin(sbuf, temp);
	}
}

int main(void)
{
	int 	fd;
	char	*line;
	// int		i = 7;

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
}
