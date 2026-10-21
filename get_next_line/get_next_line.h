/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:28:25 by deddaidi          #+#    #+#             */
/*   Updated: 2024/12/05 23:07:29 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t	ft_strlen(const char *str);
int		ft_strjoin_len(char *buf, char *full_line);
char	*ft_strjoin_g(char *buf, char *full_line);
int		check_newline(char *str);
char	*read_file(int fd, char *buf);
char	*sub_line(char *buf);
char	*clean(char *buf);
char	*get_next_line(int fd);

#endif
