/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:20:54 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/08 10:50:03 by dijonker         ###   ########.fr       */
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
	printf("\n\t     \e[1;97mCompilations: %d\n", nbr_of_compilations(system));
	return (free_for_all(system, 0));
}
