/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:46:35 by sydauria          #+#    #+#             */
/*   Updated: 2022/02/03 06:14:37 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

void	*free_this(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

void	*check_problems(void *ptr, t_Lines *first)
{
	if (!ptr && first)
	{
		while (first)
		{
			list_delone(ptr, first);
			first = first->next;
		}
	}
	return (NULL);
}

char	*list_delone(t_Lines *list, t_Lines *first)
{
	char *str;
	
	if (list->line)
		str = list->line;
	if (list->prev && !list->next)
		list->prev->next = NULL;
	else if (list->next && !list->prev)
	{
		list->next->prev = NULL;
		first = list->next;
	}
	else if (list->next && list->prev)
	{
		list->prev->next = list->next;
		list->next->prev = list->prev;
	}
	else
		first = NULL; 
	free_this(list);
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
