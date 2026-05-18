/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:56:42 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/15 15:10:52 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static t_dongle	*single_dongle(int count)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (write(2, "ERROR: create_dongle malloc failed\n", 36), NULL);
	dongle->id = count;
	dongle->c_lock = malloc(sizeof(pthread_cond_t));
	if (!dongle->c_lock)
		return (free(dongle),
			write(2, "ERROR: create_dongle malloc failed\n", 36), NULL);
	dongle->m_lock = mutex_init();
	if (!dongle->m_lock)
		return (free(dongle->c_lock), free(dongle),
			write(2, "ERROR: create_dongle mutex_init failed\n", 36),
			NULL);
	if (pthread_cond_init(dongle->c_lock, NULL) != 0)
	{
		pthread_mutex_destroy(dongle->m_lock);
		free(dongle->m_lock);
		free(dongle->c_lock);
		free(dongle);
		return (write(2, "ERROR: create_dongle pthread_cond_init failed\n", 46),
			NULL);
	}
	return (dongle);
}

int	create_dongles(t_system *system)
{
	t_dongle	**dongles;
	int			count;

	dongles = malloc((system->nbr_coders) * sizeof(t_dongle));
	if (!dongles)
		return (1);
	count = 0;
	while (count < system->nbr_coders)
	{
		dongles[count] = single_dongle(count);
		if (!*(dongles + count))
			return (1);
		dongles[count]->when_available = 0;
		dongles[count]->cooldown_time = &system->time_to_cooldown;
		dongles[count]->queue[0] = NULL;
		dongles[count]->queue[1] = NULL;
		dongles[count]->owner = 0;
		dongles[count]->next = 0;
		dongles[count]->c_locked = 0;
		system->nbr_dongles_created += 1;
		count++;
	}
	system->dongles = dongles;
	return (0);
}

static t_coder	*single_coder(t_system *system, int count)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	if (!coder)
		return (write(2, "ERROR: create_coder malloc failed\n", 35), NULL);
	coder->thread = malloc(sizeof(pthread_t));
	if (!coder->thread)
		return (free(coder),
			write(2, "ERROR: create_coder malloc failed\n", 35), NULL);
	coder->coder_lock = mutex_init();
	if (!coder->coder_lock)
		return (free(coder->thread), free(coder),
			write(2, "ERROR: create_coder mutex_init failed\n", 35), NULL);
	coder->id = count + 1;
	coder->dongle_count = 0;
	coder->loop_start_time = get_time();
	coder->program_start_time = get_time();
	coder->time_to_burnout = system->time_to_burnout;
	coder->time_to_compile = system->time_to_compile;
	coder->time_to_debug = system->time_to_debug;
	coder->time_to_refactor = system->time_to_refactor;
	coder->stop = &system->stop;
	coder->compilations = 0;
	coder->min_compilations = system->needed_compilations;
	return (coder);
}

int	create_coders(t_system *system)
{
	int		count;

	system->coders = malloc(system->nbr_coders * sizeof(t_coder));
	if (!system->coders)
		return (write(2, "ERROR: Coder malloc failed\n", 28), 1);
	count = 0;
	while (count < system->nbr_coders)
	{
		system->coders[count] = single_coder(system, count);
		if (!system->coders[count])
			return (1);
		system->coders[count]->left = system->dongles[count];
		system->coders[count]->right = system->dongles
		[(count + 1) % system->nbr_coders];
		system->coders[count]->output_log = system->output_log;
		system->coders[count]->scheduler = strcmp("fifo", system->schedule);
		system->coders[count]->monotoring_lock = system->monotoring_lock;
		system->nbr_coders_created += 1;
		count++;
	}
	return (0);
}

int	monotoring_init(t_system *system)
{
	system->monotoring = malloc(sizeof(pthread_t));
	if (!system->monotoring)
		return (write(2, "ERROR: Monotoring_init  malloc failed\n", 39), 1);
	system->output_log = mutex_init();
	if (!system->output_log)
		return (write(2, "ERROR: Monotoring_init mutex_init failed\n", 42), 1);
	system->monotoring_lock = mutex_init();
	if (!system->monotoring_lock)
		return (write(2, "ERROR: Monotoring_init mutex_init failed\n", 42), 1);
	return (0);
}
