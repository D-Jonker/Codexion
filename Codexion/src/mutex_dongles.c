/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_dongles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:23:02 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 11:07:41 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static t_dongle	*single_dongle(t_monotoring *data, int count)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->dongle_id = count;
	dongle->in_use = 0;
	if (pthread_mutex_init(&(dongle->lock), NULL) != 0)
		return (NULL);
	if (pthread_cond_init(&(dongle->available), NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->lock);
		return (NULL);
	}
	data->nbr_dongles_created += 1;
	return (dongle);
}

t_dongle	**create_dongles(t_monotoring *data)
{
	t_dongle	**dongles;
	int			count;

	count = data->nbr_of_coders - 1;
	if (count == 0)
		count = 1;
	dongles = malloc((count) * sizeof(t_dongle));
	if (!dongles)
		return (NULL);
	count = 0;
	while (count < data->nbr_of_coders - 1)
	{
		*(dongles + count) = single_dongle(data, count);
		if (!*(dongles + count))
			return (NULL);
		count++;
	}
	return (dongles);
}

int	destroy_dongles(t_dongle **dongles, int dongle_count)
{
	int				count;
	pthread_mutex_t mutex;

	count = 0;
	while (count < dongle_count)
	{
		mutex = dongles[count]->lock;
		if (pthread_mutex_destroy(&mutex) != 0)
			return (1);
		count++;
	}
	free(dongles);
	return (0);
}
