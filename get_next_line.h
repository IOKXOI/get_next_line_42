/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:23:14 by sydauria          #+#    #+#             */
/*   Updated: 2022/02/03 06:14:40 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H_
# define _GET_NEXT_LINE_H_

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <stddef.h>
#include <fcntl.h>


typedef struct s_struct
{
	struct s_struct	*prev;
	int				id;
	int				status_line;
	int				status_buffer;
	char			*line;
	char			buffer[BUFFER_SIZE + 1];
	struct s_struct	*next;
}	t_Lines;

char	*ft_strjoin(char *s1, char *s2, int k);
char	*ft_strndup(char *s, int count);
t_Lines	*where_is_my_list(int fd, t_Lines *first);
t_Lines	*create_node(int fd, t_Lines *first);
char	*get_next_line(int fd);
char	*ft_strdup(char *s);
int 	buffer_toline(t_Lines *list);
int		ft_strlen(char *str);
char	*list_delone(t_Lines *list, t_Lines *first);




# endif
