/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:20:10 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/04 10:45:52 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/source.h"

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
	system->nbr_coders = atoi(argv[1]);
	system->time_to_burnout = atoi(argv[2]);
	system->time_to_compile = atoi(argv[3]);
	system->time_to_debug = atoi(argv[4]);
	system->time_to_refactor = atoi(argv[5]);
	system->needed_compilations = atoi(argv[6]);
	system->time_to_cooldown = atoi(argv[7]);
	system->schedule = argv[8];
	system->nbr_dongles_created = 0;
	system->nbr_coders_created = 0;
	system->nbr_launched = 0;
	system->coders = NULL;
	system->dongles = NULL;
	system->monotoring = NULL;
	return (codexion(system));
}
