/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaetano <fernandacunha@id.uff.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:04:42 by fcaetano          #+#    #+#             */
/*   Updated: 2022/06/15 15:24:44 by fcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define	GET_NEXT_LINE

#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);
char    *ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);

#endif
