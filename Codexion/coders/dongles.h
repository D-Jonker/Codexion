/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:06:56 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 10:07:42 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLES_H
# define DONGLES_H
# include "source.h"

typedef struct s_dongle
{
	int				dongle_id; 			// Dongle ID as coders will take lowest id
	int				in_use; 			// If in use
	pthread_mutex_t	lock; 				// If in use the data is locked
	pthread_cond_t	available; 			// Broadcasts to this condition when the dongle is available
	t_coder			*priority_queue[2]; // 2 only two coders have access to this dongle
	long			when_available; 	// Time set down of table + cooldown time
}	t_dongle;

#endif
