/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:18:06 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/13 12:58:30 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

void	*coders_thread(void *coder_void)
{
	t_coder	*coder;

	coder = (t_coder *)coder_void;
	pthread_mutex_lock(coder->coder_lock);
	coder->loop_start_time = get_time();
	pthread_mutex_unlock(coder->coder_lock);
	while (1)
	{
		get_dongles(coder);
		compilation_stage(coder);
		release(coder, coder->left);
		release(coder, coder->right);
		debugging_stage(coder);
		refactoring_stage(coder);
		pthread_mutex_lock(coder->monotoring_lock);
		if (*coder->stop == 1)
		{
			pthread_mutex_unlock(coder->monotoring_lock);
			break ;
		}
		pthread_mutex_unlock(coder->monotoring_lock);
	}
	return (NULL);
}

int	launch_coders(t_system *system)
{
	int		count;
	t_coder	**coders;

	count = 0;
	pthread_mutex_lock(system->monotoring_lock);
	system->program_start_time = get_time();
	pthread_mutex_unlock(system->monotoring_lock);
	coders = system->coders;
	while (count < system->nbr_coders)
	{
		pthread_mutex_lock(coders[count]->coder_lock);
		coders[count]->program_start_time = system->program_start_time;
		pthread_mutex_unlock(coders[count]->coder_lock);
		if (pthread_create(coders[count]->thread, NULL,
				&coders_thread, (void *)coders[count]) != 0)
			return (1);
		system->nbr_launched += 1;
		count++;
	}
	return (0);
}

void	release(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	if (dongle->owner != coder->id)
	{
		pthread_mutex_unlock(dongle->m_lock);
		return ;
	}
	printf("\e[38;5;195m%lu  %d released %d and nw owner is %d\n", get_time() - coder->program_start_time, coder->id, dongle->id, dongle->next);
	dongle->owner = dongle->next;
	dongle->next = 0;
	coder->dongle_count -= 1;
	dongle->when_available = get_time() + *dongle->cooldown_time;
	if (dongle->c_locked == 1)
		pthread_cond_broadcast(dongle->c_lock);
	dongle->c_locked = 0;
	pthread_mutex_unlock(dongle->m_lock);
}

void	get_dongles(t_coder *coder)
{
	if (coder->scheduler != 0)
	{
		get_dongles_edf(coder);
		return ;
	}
	get_dongles_fifo(coder);
}
