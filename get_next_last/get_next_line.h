/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:18:23 by sydauria          #+#    #+#             */
/*   Updated: 2022/02/17 18:35:47 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

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

t_Lines	*create_node(int fd, t_Lines *first);
t_Lines	*where_is_my_node(int fd, t_Lines *first);
char	*fill_line(t_Lines *list);
char	*ft_memmove(char *dest, char *src, int status);
size_t	ft_strlen(char *str);
void	*free_this(void *ptr);
int		check_problems(void *ptr, t_Lines *first);
char	*list_delone(t_Lines *list, t_Lines *first);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);



#endif
