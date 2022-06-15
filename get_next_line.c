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

char *get_next_line(int fd)
{
	char *buf;
   
	buf	= calloc(sizeof(*buf), BUFFER_SIZE + 1);
	while (read(fd, buf, BUFFER_SIZE);
	{
		if (ft_strchr(buf, '\n'))
		{
			
		}
	}
	return (i);
}

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	int fd;

	fd = open("test.txt", 0);
	printf("%s\n", get_netxt_line(fd));
	return (0);
}
