/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:49:54 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/13 11:43:43 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("ERROR: Gettimeofday\n"), (size_t)(-1));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

pthread_mutex_t	*mutex_init(void)
{
	pthread_mutex_t	*location;

	location = malloc(sizeof(pthread_mutex_t));
	if (!location)
		return (NULL);
	if (pthread_mutex_init(location, NULL) != 0)
		return (free(location), NULL);
	return (location);
}

int	has_stopped(t_coder *coder)
{
	pthread_mutex_lock(coder->monotoring_lock);
	if (*coder->stop == 1)
	{
		pthread_mutex_unlock(coder->monotoring_lock);
		return (1);
	}
	pthread_mutex_unlock(coder->monotoring_lock);
	return (0);
}

int	should_release(t_coder *coder)
{
	if (has_stopped(coder) == 0)
		return (0);
	release(coder, coder->left);
	release(coder, coder->right);
	return (1);
}
