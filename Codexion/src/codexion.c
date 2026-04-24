/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:20:54 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 15:21:50 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

void	*test(void *data)
{
	t_coder *coder;

	coder = (t_coder *)data;
	usleep(1);
	printf("Coder id: %d\n", coder->coder_id);
	return (NULL);
}

static int start_threads(t_monotoring *data)
{
	int	count;

	count = 0;
	while (count < data->nbr_of_coders)
	{
		(*(data->coders) + count)->thread = (pthread_t)malloc(sizeof(pthread_t));
		if (!(*(data->coders) + count)->thread)
			return (1);
		printf("Thread: %lu\n", (*(data->coders) + count)->thread);
		if (pthread_create(&((*(data->coders) + count)->thread), NULL, &test, (void *)*(data->coders + count)) != 0)
			return (1);
		data->nbr_coders_created += 1;
		count++;
	}
	return (0);
}

int codexion(t_monotoring *data)
{
	data->dongles = create_dongles(data);
	data->coders = create_coders(data);
	if (!data->dongles || !data->coders)
		return (1);
	printf("Hi %d/%d %d/%d\n", data->nbr_coders_created, data->nbr_of_coders, data->nbr_dongles_created, data->nbr_of_coders -1);
	if (data->nbr_coders_created == data->nbr_of_coders
		&& data->nbr_dongles_created == data->nbr_of_coders - 1)
	{
		data->nbr_coders_created = 0;
		printf("Flag\n");
		if (start_threads(data) == 1)
			return (join_coders(data->coders, data->nbr_of_coders), 1);
		printf("Flag 2\n");
		join_coders(data->coders, data->nbr_of_coders);
	}
	printf("Flag 3\n");
	free_for_all(data);
	return (0);
}