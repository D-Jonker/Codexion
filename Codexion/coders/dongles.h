/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:06:56 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/13 12:18:52 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLES_H
# define DONGLES_H
# include "source.h"

typedef struct s_dongle
{
	int				id;
	int				owner;
	int				next;
	pthread_mutex_t	*m_lock;
	pthread_cond_t	*c_lock;
	int				c_locked;
	void			*queue[2];
	size_t			when_available;
	int				*cooldown_time;
}	t_dongle;

#endif
