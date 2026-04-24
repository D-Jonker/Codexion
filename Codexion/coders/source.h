/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:06:43 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 11:23:04 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include "coders.h"
# include "dongles.h"
# include "monotoring.h"

char		*ft_strdup(const char *s);

void		free_for_all(t_monotoring *data);

int			codexion(t_monotoring *data);

t_dongle	**create_dongles(t_monotoring *data);
int			destroy_dongles(t_dongle **dongles, int dongle_count);

t_coder		**create_coders(t_monotoring *data);
int			join_coders(t_coder **coders, int coder_count);

void		*compilation_stage(int current_time, int coder_id, int sleep_time);
void		*debugging_stage(int current_time, int coder_id, int sleep_time);
void		*refactoring_stage(int current_time, int coder_id, int sleep_time);

#endif