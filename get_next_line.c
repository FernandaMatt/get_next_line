/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:05:12 by fcaetano          #+#    #+#             */
/*   Updated: 2022/06/15 15:30:34 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char		*next_buf;
	char		*buf;
	static char	*sbuf;
	char		*temp;
	int		nli;

	next_buf = malloc(BUFFER_SIZE);
	buf = sbuf;
	while (read(fd, next_buf, BUFFER_SIZE))
	{
		temp = ft_strjoin(buf, next_buf);
		free(buf);
		buf = temp;
		nli = ft_strchr(buf, '\n');
		if (nli >= 0)
		{
			sbuf = ft_substr(buf, nli, BUFFER_SIZE - nli);
			temp = ft_substr(buf, 0, nli + 1);
			free(buf);
			return (temp);
		}
	}
}

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	int fd;

	fd = open("test.txt", 0);
	printf("%s\n", get_next_line(fd));
	return (0);
}
