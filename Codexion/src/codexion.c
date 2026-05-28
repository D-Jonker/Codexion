/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:20:54 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/22 10:11:34 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static int	nbr_of_compilations(t_system *system)
{
	int	count;
	int	tally;

	count = 0;
	tally = 0;
	while (count < system->nbr_coders_created)
	{
		tally += system->coders[count]->compilations;
		count++;
	}
	return (tally);
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

int	codexion(t_system *system)
{
	system->stop = 0;
	if (monotoring_init(system) != 0)
		return (free_for_all(system, 0));
	if (create_dongles(system) != 0 || create_coders(system) != 0)
		return (free_for_all(system, 0));
	if (pthread_create(system->monotoring, NULL, &monotoring, (void *)system)
		|| launch_coders(system) != 0)
		return (join_coders(system), free_for_all(system, 0));
	if (join_coders(system))
		return (free_for_all(system, 0));
	if (pthread_join(*system->monotoring, NULL) != 0)
		return (free_for_all(system, 0));
	printf("\n\t     \e[1;97mCompilations: %d/%d\n",
		nbr_of_compilations(system),
		system->nbr_coders * system->needed_compilations);
	return (free_for_all(system, 0));
}
