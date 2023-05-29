/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-sous <tde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:10:22 by tde-sous          #+#    #+#             */
/*   Updated: 2023/05/27 16:35:04 by tde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef ARRAY_MAX_SIZE
#  define ARRAY_MAX_SIZE 4096
# endif

/**
 * @brief This function requires a filedescriptor and return the next
 * line.
 *
 * @param fd File Descriptor
 * @return Next line in the file or NULL.
 */
char			*get_next_line(int fd);
char			*ft_strchr(const char *str, int chr);
char			*ft_strjoin(const char *s1, const char *s2);
void			*ft_calloc(size_t nmemb, size_t size);
//static char		*ft_get_stash(char *line);
char			*ft_get_all(int fd, char *buffer, char *stash);
size_t			ft_strlen(const char *str);
int				ft_check_newline(char *str);

#endif
