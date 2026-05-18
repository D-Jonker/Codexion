/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monotoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:27:20 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/18 09:19:39 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static int	should_continue(t_system *system)
{
	int	i;
	int	tally;

	tally = 0;
	i = 0;
	while (i < system->nbr_coders)
	{
		pthread_mutex_lock(system->coders[i]->coder_lock);
		tally += system->coders[i]->compilations;
		pthread_mutex_unlock(system->coders[i]->coder_lock);
		i++;
	}
	if (tally >= system->nbr_coders * system->needed_compilations)
		return (0);
	return (1);
}

static int	check_burnout(t_system *system, int i)
{
	pthread_mutex_lock(system->coders[i]->coder_lock);
	if (get_time() >= (size_t)system->time_to_burnout
		+ system->coders[i]->loop_start_time)
	{
		pthread_mutex_unlock(system->coders[i]->coder_lock);
		return (1);
	}
	pthread_mutex_unlock(system->coders[i]->coder_lock);
	return (0);
}

void	*monotoring(void *sys)
{
	t_system	*system;
	int			i;

	system = (t_system *)sys;
	while (should_continue(system))
	{
		i = 0;
		while (i < system->nbr_coders)
		{
			if (should_continue(system) && check_burnout(system, i))
			{
				log_msg(system->coders[i], "!!!BURNOUT!!!", "\e[38;5;196m");
				pthread_mutex_lock(system->monotoring_lock);
				system->stop = 1;
				pthread_mutex_unlock(system->monotoring_lock);
				return (0);
			}
			i++;
		}
		usleep(500);
	}
	pthread_mutex_lock(system->monotoring_lock);
	system->stop = 1;
	pthread_mutex_unlock(system->monotoring_lock);
	return (0);
}
