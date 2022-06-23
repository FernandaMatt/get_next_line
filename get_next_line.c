/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:05:12 by fcaetano          #+#    #+#             */
/*   Updated: 2022/06/20 16:44:31 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"

//#define BUFFER_SIZE 42
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);
char    *ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);

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

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
	char    *substr;

	if (start >= ft_strlen(s))
		return(ft_strdup(""));
	substr = malloc((len+1)*sizeof(*s));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, &s[start], len+1);
	return (substr);
}

char	*ft_strdup(const char *src)
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

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*newstr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	newstr = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!newstr)
		return (newstr);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstr + ft_strlen(s1), s2, ft_strlen((char *)s2) + 1);
	return (newstr);
}

void	*ft_calloc(size_t count, size_t size)
{
		void *ptr;
		int i;

		ptr = malloc(count*size);
		if (ptr == NULL)
				return (ptr);
		i = count * size - 1;
		while (i >= 0)
				((char *)ptr)[i--] = 0;
		return (ptr);
}

/* char	*check_readbytes(char *buf)
{
	int nli;
	char *temp;
	static char	*sbuf;

	if (buf)
	{
		temp = sbuf;
		sbuf = ft_strjoin()
	}
} */

char *get_next_line(int fd)
{
	char		*next_buf;
	char		*buf;
	static char	*sbuf;
	char		*temp;
	int			nli;
	int			bread;

	if (fd < 0)
		return (0);
	buf = sbuf;
	nli = ft_strchr(sbuf, '\n');
	if (nli >= 0)
	{
		temp = ft_substr(buf, 0, nli + 1);
		sbuf = ft_strdup(buf + nli + 1);
		if (!ft_strlen(sbuf))
			{
				free(sbuf);
				sbuf = 0;
			}
		free(buf);
		return (temp);
	}
	next_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(*next_buf));
	bread = read(fd, next_buf, BUFFER_SIZE);
	if (bread <= 0 && !ft_strlen(buf))
	{
		free(sbuf);
		free(next_buf);
		return (0);
	}
	while (bread)
	{
		next_buf[bread] = 0;
		temp = ft_strjoin(buf, next_buf);
		if(buf)
			free(buf);
		buf = temp;
		nli = ft_strchr(buf, '\n');
		if (nli >= 0)
		{
			sbuf = ft_strdup(buf + nli + 1);
			temp = ft_substr(buf, 0, nli + 1);
			free(buf);
			free(next_buf);
			return (temp);
		}
		bread = read(fd, next_buf, BUFFER_SIZE);
	}
	if(buf)
	{
		temp = buf;
		free(next_buf);
		sbuf = 0;
		return (temp);
	}
	return (0);
}

/* #include <fcntl.h>
int main(void)
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
