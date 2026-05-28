/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:20:10 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/21 15:49:53 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/source.h"

static int	numeric_validation(t_system *system)
{
	if (system->nbr_coders < 0)
		return (1);
	if (system->time_to_burnout < 0)
		return (1);
	if (system->time_to_compile < 0)
		return (1);
	if (system->time_to_debug < 0)
		return (1);
	if (system->time_to_refactor < 0)
		return (1);
	if (system->needed_compilations < 0)
		return (1);
	if (system->time_to_cooldown < 0)
		return (1);
	return (0);
}

static void	assign_atoi(char **argv, t_system *system)
{
	system->nbr_coders = atoi(argv[1]);
	system->time_to_burnout = atoi(argv[2]);
	system->time_to_compile = atoi(argv[3]);
	system->time_to_debug = atoi(argv[4]);
	system->time_to_refactor = atoi(argv[5]);
	system->needed_compilations = atoi(argv[6]);
	system->time_to_cooldown = atoi(argv[7]);
	system->schedule = argv[8];
}

int	main(int argc, char **argv)
{
	t_system	*system;

	if (argc != 9 || !argv || !*argv)
		return (write(2, "Provide all arguments\n", 24), 0);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (write(2, "Only \'fifo\' and \'edf\' allowed for schedule\n",
				44), 0);
	system = malloc(sizeof(t_system));
	if (!system)
		return (1);
	assign_atoi(argv, system);
	if (numeric_validation(system))
		return (write(2, "0 < input < INT_MAX\n", 38), 0);
	system->nbr_dongles_created = 0;
	system->nbr_coders_created = 0;
	system->nbr_launched = 0;
	system->coders = NULL;
	system->dongles = NULL;
	system->monotoring = NULL;
	return (codexion(system));
}
