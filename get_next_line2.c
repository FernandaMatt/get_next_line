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

#define BUFFER_SIZE 1
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);
char    *ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strchr(const char *s, int c);
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
	char	*temp;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		temp = ft_strdup(s1);
		free(s1);
		return (temp);
	};
	newstr = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!newstr)
		return (newstr);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstr + ft_strlen(s1), s2, ft_strlen((char *)s2) + 1);
	free(s1);
	return (newstr);
}

char	*check_readbytes(char *buf, int bread)
{
	int nli;
	char *temp;
	static char	*sbuf;
	
	if (buf && ft_strlen(buf))
		sbuf = ft_strjoin(sbuf, buf);
	if (buf)
		free (buf);
	nli = ft_strchr(sbuf, '\n');
	if (nli >= 0)
	{
		temp = ft_substr(sbuf, 0, nli + 1);
		sbuf = ft_strdup(sbuf + nli + 1);
		if (!ft_strlen(sbuf))
			{
				free(sbuf);
				sbuf = 0;
			}
		return (temp);
	}
	if (!bread)
	{
		temp = sbuf;
		sbuf = 0;
		return (temp);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			bread;

	if (fd < 0)
		return (0);
	buf = 0;
	buf = check_readbytes(buf, 1);
	if (buf)
		return (buf);
	buf = malloc(BUFFER_SIZE + 1 * sizeof(*buf));
	bread = read(fd, buf, BUFFER_SIZE);
	if (bread < 0)
	{
		free(buf);
		return (0);
	}
	while (bread > 0)
	{
		buf[bread] = 0;
		buf = check_readbytes(buf, bread);
		if (buf)
			return (buf);
		buf = malloc(BUFFER_SIZE + 1 * sizeof(*buf));
		bread = read(fd, buf, BUFFER_SIZE);
	}
	buf = check_readbytes(buf, bread);
	if (buf)
		return (buf);
	return (0);
}

#include <fcntl.h>
int main(void)
{
	int 	fd;
	char	*line;

	fd = open("test2.txt", 0);
	
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
