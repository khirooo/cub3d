/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:56:37 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/05 17:05:05 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
int		ft_strlen2(char *s);
int		ft_new_line(char *s);
void	ft_copy(char *dest, char *src, int size);
char	*init_buffer(size_t size, char *buffer);
char	*ft_append(char	*dest, char	*src);
#endif