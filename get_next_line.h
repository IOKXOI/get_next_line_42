/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:23:14 by sydauria          #+#    #+#             */
/*   Updated: 2022/01/28 16:32:31 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H_
# define _GET_NEXT_LINE_H_

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <stddef.h>
#include <fcntl.h>


typedef struct t_struct
{
	int				id;
	int				status_line;
	int				status_buffer;
	char			*line;
	char			*buffer;
	struct t_struct	*next;
}	S_Lines;

char	*ft_strjoin(char *s1, char *s2, int k);
char	*ft_strndup(char *s, int count);
S_Lines *where_is_my_list(int fd, S_Lines *first);
S_Lines *create_node(int fd, S_Lines *first);
int		check_buff(S_Lines *list);
int 	free_all(S_Lines *list);
char	*get_next_line(int fd);
char	*ft_strdup(char *s);
int 	print_list(S_Lines *list);
int 	buffer_toline(S_Lines *list);




# endif
