/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:46:35 by sydauria          #+#    #+#             */
/*   Updated: 2022/01/30 01:59:04 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

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

char	*ft_strjoin(char *s1, char *s2, int k)
{
	char	*s3;
	int 		i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if(!s2)
		return (NULL);
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

char	*ft_strndup(char *s, int count)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	while (s[i] && count--)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	str = NULL;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	//free(s);
	str[i] = '\0';
	return (str);
}


int print_list(S_Lines *list, char *buffer)
{
	printf("==============================================\n");
	printf("ID = %d \nSTATUS_LINE = %d\nSTATUS_BUFFER = %d\nLine =%s \nBuffer = %s\buffer_residue = %d\n",list->id,list->status_line, list->status_buffer, list->line, list->buffer, list->count_char);
	printf("==============================================\n");
	if (!buffer)
		return (0);
	printf("buffer = %s\n\n", buffer);
	return 0;
}

/*
char	*buff_to_line(S_Lines *list, int fd, char *buff)
{
	int		i;
	char	*str;
	char	*temp_buff;
	char	*end;

	i = 0;

	temp_buff = malloc(1);
	str = malloc(1);
	temp_buff[0] = '\0';
	str[0] = '\0';
	print_list(list);

	while (list->buffer[i] != '\n' && list->buffer[i] != '\0')
	{
		if (!(++i < BUFFER_SIZE) || !(list->buffer[i]))
		{
			printf("=====I depasse le buffer size =====\n");
			printf("VRAI BUFFER = %s \n", buff);
			print_list(list);

			temp_buff = ft_strndup(buff, i);
			str = ft_strjoin(str, temp_buff);
			if(list->line && (strlen(list->line) > 0))
				free (list->line);
			list->line = ft_strdup(str);
			if (read(fd, buff, BUFFER_SIZE) < 1)
				return ("fin de fichier\n");
			fill_buff(list, buff);
			i = 0;
		}
	}
	end = ft_strndup(buff, i);
	list->line = ft_strjoin(str, end);
	list->buffer = ft_strndup(&buff[i], BUFFER_SIZE);
*/
