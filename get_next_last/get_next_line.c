/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:16:58 by sydauria          #+#    #+#             */
/*   Updated: 2022/02/17 19:34:03 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_Lines	*where_is_my_node(int fd, t_Lines *first)
{
	t_Lines	*list;

	list = first;
	if (first)
	{
		while (list->next && list->id != fd)
			list = list->next;
		if (list->id == fd)
		{
			list->line = NULL;
			list->status_line = 0;
			return (list);
		}
	}
	list = create_node(fd, first);
	first = list;
	if (check_problems(list, first))
		return (NULL);
	return (first, list);
}

t_Lines	*create_node(int fd, t_Lines *first)
{
	t_Lines	*new_link;
	
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
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	str = NULL;
	while (list->buffer[i] && list->buffer[i] != '\n')
		i++;	
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	str[i + 1] = '\0';
	while (++j <= i)
		str[j] = list->buffer[j];
	if (str[i] == '\n')
		list->status_line = 1;
	ft_memmove(&list->buffer[0], &list->buffer[j], 0);
	if (list->buffer[0] == '\0')
		list->status_buffer = 0;
	return (str);
}

char	*ft_memmove(char *dest, char *src, int status)
{
	size_t	i;
	
	i = 0;
	if (dest == src && status == 1)
	{
		while (i <= BUFFER_SIZE)
			dest[i++] = '\0';
	}
	else
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
	}
	while (i <= BUFFER_SIZE)
		dest[i++] = '\0';
	return (dest);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*free_this(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (ptr);
}

int	check_problems(void *ptr, t_Lines *first)
{
	if (!ptr)
	{
		while (first)
		{
			list_delone(ptr, first);
			first = first->next;
		}
		return (1);
	}
	return (0);
}

char	*list_delone(t_Lines *list, t_Lines *first)
{
	char	*str;

	str = NULL;
	(void)first;
	if (list->line)
		str = list->line;
	if (list->next && !list->prev)
	{
		list->next->prev = NULL;
		first = list->next;
	}
	else if (list->prev && !list->next)
		list->prev->next = NULL;
	else if (list->next && list->prev)
	{
		list->prev->next = list->next;
		list->next->prev = list->prev;
	}
	else
	{
		first = free_this(list);
		return (str);
	}
	return (free_this(list), str);
}

/*char	*ft_memmove(char *dest, char *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	if (src == dest)
	{
		while (dest[i])
			dest[i++] = '\0';
	}
	else if (src > dest)
	{
		while (src[i] && size--)
		{
			dest[i] = src[i];
			i++;
		}
	}
	while (i <= BUFFER_SIZE)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}*/

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			s3[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	if (s1)
		free_this(s1);
	if (s2)
		free_this(s2);
	return (s3);
}


char	*get_next_line(int fd)
{
	t_Lines			*list;
	static t_Lines	*first = NULL;
	char			*str;

	list = where_is_my_node(fd, first);
	if (!list)
	{
		first = create_node(fd, first)
	}
		return (NULL);
	while (list->status_line != 1)
	{
		if (list->status_buffer == 0)
		{
			if (read(fd, list->buffer, BUFFER_SIZE) < 1)
				return (list_delone(list, first));
			list->status_buffer = 1;
		}
		str = fill_line(list);
		if (check_problems(str, first))
			return (NULL);
		list->line = ft_strjoin(list->line, str);
		if (check_problems(list->line, first))
			return (NULL);
	}
	return (list->line);
}
