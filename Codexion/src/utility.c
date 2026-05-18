/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:49:54 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/18 11:30:10 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

size_t	get_loop_start(t_coder *coder)
{
	size_t	time;

	pthread_mutex_lock(coder->coder_lock);
	time = coder->loop_start_time;
	pthread_mutex_unlock(coder->coder_lock);
	return (time);
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

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("ERROR: Gettimeofday\n"), (size_t)(-1));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

void	log_msg(t_coder *coder, char *msg, char *colour)
{
	if (has_stopped(coder) == 1)
		return ;
	pthread_mutex_lock(coder->output_log);
	pthread_mutex_lock(coder->coder_lock);
	printf("  %s%10lu %3d %s\n\e[38;5;252m",
		colour,
		get_time() - coder->program_start_time,
		coder->id,
		msg);
	pthread_mutex_unlock(coder->coder_lock);
	pthread_mutex_unlock(coder->output_log);
}
