/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:20:10 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 14:45:09 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/source.h"

static t_monotoring	*monotoring_init(void);

static t_monotoring	*monotoring_init(void)
{
	t_monotoring	*data;

	data = malloc(sizeof(t_monotoring));
	if (!data)
		return (NULL);
	data->nbr_dongles_created = 0;
	data->nbr_coders_created = 0;
	data->nbr_of_coders_launched = 0;
	data->nbr_of_coders = 9;
	data->needed_compilations = 111;
	data->time_to_burnout = 21;
	data->time_to_compile = 5;
	data->time_to_debug = 5;
	data->time_to_refactor = 5;
	data->time_to_cooldown = 5;
	data->scheduler = ft_strdup("Fifo");
	return (data);
}

int	main(void)
{
	t_monotoring	*data;
	int				error;

	data = monotoring_init();
	if (!data || !data->scheduler)
		return (1);
	error = codexion(data);
	free(data);
	if (error == 1)
		return (1);
	return (0);
}
