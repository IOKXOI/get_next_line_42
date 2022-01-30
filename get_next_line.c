/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 03:19:34 by sydauria          #+#    #+#             */
/*   Updated: 2022/01/30 01:53:43 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"
#include <string.h>

S_Lines *where_is_my_list(int fd, S_Lines *first)
{
	S_Lines *list;
	list = first;
	if (list == NULL)
		return (NULL);
	while (list->next && list->id != fd)
		list = list->next;
	if (list->id == fd)
		return (list);
	return (NULL);
}

S_Lines *create_node(int fd, S_Lines *first)
{
	S_Lines *new_link;

	if (first == NULL)
	{
		first = malloc(sizeof(S_Lines));
		if (!first)
			return (NULL);
		first->id = fd;
		first->status_line = 0;
		first->status_buffer = 0;
		first->buffer_residue = BUFFER_SIZE;
		first->next = NULL;
		first->line = NULL;
		first->buffer = NULL;
										printf(".ETAPE : Create new list d'ID -> %d \n", first->id);
		return (first);
	}
	new_link = malloc(sizeof(S_Lines));
	if (!new_link)
		return (NULL);
	new_link->id = fd;
	new_link->status_line = 0;
	new_link->status_buffer = 0;
	new_link->buffer_residue = BUFFER_SIZE;
	new_link->line = NULL;
	new_link->buffer = NULL;
										printf(".ETAPE : Create new maillon d'ID -> %d \n", new_link->id);
	new_link->next = first;
	return (new_link);
}

int fill_buffer(S_Lines *list, char *buffer, int fd)
{
	int	nb;

	if (list->status_buffer == 0)      printf("BUFFER = %s STATUS_BUFFER = %d \n", list->buffer, list->status_buffer);

	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb < 1)
			return (0);
		list->buffer = ft_strndup(buffer, nb);
		list->status_buffer = 1;
										//printf(".ETAPE : remplissage du buffer. Nous avons lu %d caractères \n", nb);
	}
	return (nb);
}

int	fill_line(S_Lines *list, int nb)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i < list->buffer_residue && list->buffer[i] != '\n' && list->buffer[i] != '\0')
		i++;
	if (i < list->buffer_residue && list->buffer[i] == '\n'|| list->buffer[i] == '\0') 			//Nous allons copier un \n ou \0, donc la line sera bonne, on passe son status a 1.
	{
		list->status_line = 1;
	}
	temp = ft_strdup(list->line);
	list->line = ft_strjoin(temp, list->buffer, i);						// On joint i charactères de list->buffer à list->line
	if (++i < list->buffer_residue)														// Si le buffer contient encore des caractères derrieres on dup le reste du buffer dans temp.
	{
		temp = ft_strndup(&list->buffer[i], nb);
		//free(list->buffer);												//On free le list->buffer et on lui assigne ce qui restait dans le buffer.
		list->buffer = temp;
		list->status_buffer = 1;										// List->buffer n'est pas vide, on passe son status a 1 pour ne pas read avant utiliser ca.
	}
	else
	{
		list->status_buffer = 0;										//Si on a mis la totalité de list->buffer dans list->line, alors on passe le status à 0 et on free.
		//free(list->buffer);
	}
	return (ft_strlen(list->buffer));
}

char	*get_next_line(int fd)
{
	int				nb;
	char			buffer[BUFFER_SIZE + 1];
	S_Lines			*list;
	static S_Lines	*first = NULL;

	buffer[BUFFER_SIZE] = '\0';
	printf("ETAPE where is my list\n");
	list = where_is_my_list(fd, first); // Fonction qui cherche la liste correspondante au fd. Si on ne la trouve pas (peut etre est elle inexistante), on return NULL.
	printf("ETAPE where is my list fini\n");


	if (list == NULL)
	{
		list = create_node(fd, first);  // La liste n'existe pas, nous la créons, et nous la mettons en premier. Toute les valeurs sont initialisées sur NULL ou 0.
		first = list;
	}
	//if(!list->status_line)
    	print_list(list, buffer);

	list->status_line = 0;              // Status_line indique par 0, que la line ne contient pas de \n ou \0. Nous l'initialisons a 0, car lorsque l'on return la ligne correctement, cela veut dire que la valeur est sur 1.
	printf("Initialisation status_line = 0\n");
	print_list(list, buffer);
	while (list->status_line != 1)		// On boucle tant que la ligne ne contient pas de \n ou \0.
	{
		if (list->status_buffer == 0)	// Status_buffer == 0 veut dire que le list->buffer est vide. On doit donc dup le char *buffer que l'on remplis avec read().
		{
			printf("Status_buffer = 0 donc fill buff\n");
			nb = fill_buffer(list, buffer, fd);
			if (nb < 1)
				return ("FINITO");//free_all(list));
			printf("fill buff fait\n");
			print_list(list, buffer);

		}
		printf("REMPLISSAGE EN BOUCLE DE LA LIGNE TANT QUE STATUS LINE !=1 \n");
		print_list(list, buffer);

		list->buffer_residue = fill_line(list, nb);			// On remplis la ligne en utilisant list->buffer. Si en copiant, on se rend compte qu'on copie un \n ou \0, on passe le status_line a 1. Ainsi on sort dde la boucle et on return la line.
		printf("REMPLISSAGE FAIT \n");
		print_list(list, buffer);
	}
	printf("STATUS LINE =1 ON SORT DE LA BOUCLE EST ON RETURN \n");
	print_list(list, buffer);
	return (list->line);
}
