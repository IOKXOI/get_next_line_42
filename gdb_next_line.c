/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdb_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 03:19:34 by sydauria          #+#    #+#             */
/*   Updated: 2022/02/03 06:14:34 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"
#include <string.h>

t_Lines *where_is_my_list(int fd, t_Lines *first)
{
	t_Lines *list;
	list = first;
	if (list == NULL)
		return (NULL);
	while (list->next && list->id != fd)
		list = list->next;
	if (list->id == fd)
	{
		list->line = NULL;
		list->status_line = 0;
		return (list);
	}
	return (NULL);
}

t_Lines *create_node(int fd, t_Lines *first)
{
	t_Lines *new_link;

	new_link = malloc(sizeof(t_Lines));
	if (!new_link)
		return (NULL);
	new_link->prev = NULL;
	new_link->id = fd;
	new_link->status_line = 0;
	new_link->status_buffer = 0;
	new_link->line = NULL;
	new_link->buffer[BUFFER_SIZE] = '\0';
	if (first == NULL)
	{
		new_link->next = NULL;
		first = new_link;
		return (first);
	}
	new_link->next = first;
	first->prev = new_link;
	first = new_link;
	return (first);
}

char	*fill_line(t_Lines *list)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = -1;
	str = NULL;
	while (list->buffer[i] && list->buffer[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	while (++j <= i)
		str[j] = list->buffer[j];
	if (str[i] == '\n')
		list->status_line = 1;
//	ft_memmove(list->buffer[0], list->buffer[i], i);
	if (!list->buffer[0])
		list->status_buffer = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2, int k)
{
	char	*s3;
	int 	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (s2);
	if(!s2)
		return (s1);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] && i <= k)
		s3[j++] = s2[i++];
	s3[j] = '\0';
	free(s1);
	return (s3);
}

char	*get_next_line(int fd)
{
	t_Lines			*list;
	static t_Lines	*first = NULL;
	char			*str;

	str = NULL;	
	list = where_is_my_list(fd, first); 
	if (list == NULL)
		list = create_node(fd, first);  
	while (list->status_line != 1)
	{
		if (list->status_buffer == 0)	
		{
			if (read(fd, list->buffer, BUFFER_SIZE) < 1)
				return (list_delone(list, first));
			list->status_buffer = 1;
		}
		str = ft_strjoin(str, fill_line(list));
	}
	return (str);
}
