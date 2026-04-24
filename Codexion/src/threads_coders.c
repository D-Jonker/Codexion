/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_coders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:18:06 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 15:20:54 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static t_coder	*single_coder(t_monotoring *data, int count);

/**
 * @brief 
 * 
 * @param data 
 * @param count 
 * @return t_coder* 
 */
static t_coder	*single_coder(t_monotoring *data, int count)
{
	t_coder *coder;

	coder = malloc(sizeof(coder));
	if (!coder)
		return (NULL);
	coder->coder_id = count + 1;
	coder->dongle_count = 0;
	coder->start_time = 0;
	coder->start_compiling = 0;
	coder->start_debug = 0;
	coder->start_refactor = 0;
	data->nbr_coders_created += 1;
	return (coder);
}

/**
 * @brief Create a coders object
 * 
 * @param data 
 * @return t_coder** 
 */
t_coder **create_coders(t_monotoring *data)
{
	t_coder	**coders;
	int		count;

	coders = malloc(data->nbr_of_coders * sizeof(t_coder));
	if (!coders)
		return (NULL);
	count = 0;
	while (count < data->nbr_of_coders)
	{
		*(coders + count) = single_coder(data, count);
		if (!*(coders + count))
			return (NULL);
		count++;
	}
	return (coders);
}

/**
 * @brief This joins all the coder threads back into one
 * 
 * @param coders The array storing all the created threads 
 * 				 in sequential order
 * @param coder_count The number of coders created
 *
 * @return int 1 if failed to join a thread, 0 if succeeds joining all
 */
int	join_coders(t_coder **coders, int coder_count)
{
	int			count;
	pthread_t	twine;

	count = 0;
	while (count < coder_count)
	{
		twine = coders[count]->thread;
		// pthread_join(twine, NULL);
		if (pthread_join(twine, NULL) != 0)
			return (1);
		count++;
	}
	return (0);
}
