/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_for_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:09:26 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/18 12:09:50 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static int	destroy_dongles(t_system *system)
{
	int	count;

	count = 0;
	while (count < system->nbr_dongles_created)
	{
		if (pthread_mutex_destroy((system->dongles)[count]->m_lock) != 0)
			write(2, "ERROR: mutex_destroy dongles failed\n", 37);
		free((system->dongles)[count]->m_lock);
		(system->dongles)[count]->m_lock = NULL;
		if (pthread_cond_destroy((system->dongles)[count]->c_lock) != 0)
			write(2, "ERROR: cond_destroy dongles failed\n", 36);
		free((system->dongles)[count]->c_lock);
		(system->dongles)[count]->c_lock = NULL;
		free((system->dongles)[count]);
		(system->dongles)[count] = NULL;
		count++;
	}
	free(system->dongles);
	system->dongles = NULL;
	return (0);
}

static int	destroy_coders(t_system *system)
{
	int		count;
	t_coder	*coder;

	count = 0;
	while (count < system->nbr_coders_created)
	{
		coder = (system->coders)[count];
		free(coder->thread);
		if (pthread_mutex_destroy(coder->coder_lock) != 0)
			write(2, "ERROR: destroying coder_lock failed\n", 37);
		free(coder->coder_lock);
		coder->coder_lock = NULL;
		free(coder);
		coder = NULL;
		count++;
	}
	free(system->coders);
	system->coders = NULL;
	return (0);
}

int	free_for_all(t_system *system, int mode)
{
	if (system->monotoring)
		free(system->monotoring);
	if (system->output_log)
	{
		if (pthread_mutex_destroy(system->output_log) != 0)
			write(2, "ERROR: destroying output_log failed\n", 37);
		free(system->output_log);
		system->output_log = NULL;
	}
	if (system->monotoring_lock)
	{
		if (pthread_mutex_destroy(system->monotoring_lock) != 0)
			write(2, "ERROR: destroying monotoring_lock failed\n", 42);
		free(system->monotoring_lock);
		system->monotoring_lock = NULL;
	}
	if (system->dongles)
		destroy_dongles(system);
	if (system->coders)
		destroy_coders(system);
	free(system);
	return (mode);
}

int	join_coders(t_system *system)
{
	int	i;

	i = 0;
	while (i < system->nbr_launched)
	{
		if (pthread_join(*(system->coders[i]->thread), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
