/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:06:43 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/22 10:13:00 by dijonker         ###   ########.fr       */
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
# include "dongles.h"
# include "coders.h"
# include "system.h"

/**
 * @brief	The main cordinater of the creation and desruction of all
 * 			stuct, threads and malloced data.
 * 
 * @param	system
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->output_log is a mutex to ensure all messages are printed
 * 			proper sequential order
 * 
 * 			system->monotoring is the monotoring thread managing burnout time
 * 
 *			system->stop is a a variable all coders point to. This is so that
 *			coder threads can validate if they should continue or end the program
 *			This is raised when the number of required compilations has been
 *			reached or the program has burntout
 * 
 * @return	int
 * 			Returns 0 if the program has eneded properly
 * 			Returns 1 if a unspecified error occurs
 */
int				codexion(t_system *system);

/**
 * @brief	Get the loop start object
 * 			Retrieves the loop_start_time attribute of the coder struct
 * 
 * @param	coder
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread
 * @return	size_t
 * 			The time in miliseconds when the loop started
 */
size_t			get_loop_start(t_coder *coder);

/**
 * @brief	Creates a mutex instance that can be pointed at by a pointer
 * 
 * @return	pthread_mutex_t*
 * 			Pointer to an initialised mutex
 */
pthread_mutex_t	*mutex_init(void);

/**
 * @brief	Get the time object
 * 			uses the sys/time module to get the current time in miliseconds
 * 
 * @return size_t 
 */
size_t			get_time(void);

/**
 * @brief 	Lock and reads the system->stop attribute each coder has a pointer to
 * 
 * @param	coder 
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread
 * 
 * @return	int 
 * 			Returns the curent value of stop
 */
int				has_stopped(t_coder *coder);

/**
 * @brief	Prints a speciic message in terminal whci is timestamped ftrom since
 * 			the program started
 * 
 * @param	coder
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread. This is read for the necessary paramaters a log
 * 			should include
 * 
 * @param	msg
 * 			Added message to be printed along the timestamp
 * 
 * @param	colour
 * 			Valid ANSI clour code for the colour of the log
 */
void			log_msg(t_coder *coder, char *msg, char *colour);

/**
 * @brief 	Initialises the monotoring thread with the necessary attribute values
 * 			mutexes and conds.
 * 
 * @param	system
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->output_log is a mutex to ensure all messages are printed
 * 			proper sequential order
 * 
 * 			system->monotoring is the monotoring thread managing burnout time
 * 
 *			system->stop is a a variable all coders point to. This is so that
 *			coder threads can validate if they should continue or end the program
 *			This is raised when the number of required compilations has been
 *			reached or the program has burntout
 * 
 * @return	int 
 */
int				monotoring_init(t_system *system);

/**
 * @brief	The set instructions a monotoring thread follows repeatedly
 * 
 * @param	system 
 * 
 * @return	void*
 * 			NULL and only void* to fit with requied paramaters for a
 * 			pthread_create. No other values are required as all cases that
 * 			create catchable errors are exterior to the threads
 */
void			*monotoring(void *system);

/**
 * @brief	Create a dongles object
 * 			Creates all the necessary dongles, assigning paramaters, 
 * 			initialises mutexes and con_mutexes.
 * 
 * @param	system
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->output_log is a mutex to ensure all messages are printed
 * 			proper sequential order
 * 
 * 			system->monotoring is the monotoring thread managing burnout time
 * 
 *			system->stop is a a variable all coders point to. This is so that
 *			coder threads can validate if they should continue or end the program
 *			This is raised when the number of required compilations has been
 *			reached or the program has burntout
 *
 * @return	int 
 * 			Returns 1 in case of failure and 0 when no errors occur
 */
int				create_dongles(t_system *system);

/**
 * @brief	Create and initialises all the attributes and mutexes of
 * 			a coder struct. Also points to the the correct dongles and
 * 			other system wide variables
 * 
 * @param	system
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->output_log is a mutex to ensure all messages are printed
 * 			proper sequential order
 * 
 * 			system->monotoring is the monotoring thread managing burnout time
 * 
 *			system->stop is a a variable all coders point to. This is so that
 *			coder threads can validate if they should continue or end the program
 *			This is raised when the number of required compilations has been
 *			reached or the program has burntout
 * 
 * @return t_coder** an array of t_coder with memory allocated to start a
 * 		   thread lather
 */
int				create_coders(t_system *system);

/**
 * @brief 	Starts all the coder threads
 * 
 * @param	system
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->output_log is a mutex to ensure all messages are printed
 * 			proper sequential order
 * 
 * 			system->monotoring is the monotoring thread managing burnout time
 * 
 *			system->stop is a a variable all coders point to. This is so that
 *			coder threads can validate if they should continue or end the program
 *			This is raised when the number of required compilations has been
 *			reached or the program has burntout
 *
 * @return	int 
 * 			Returns 1 in case of aerror and 0 if everything went well
 */
int				launch_coders(t_system *system);

/**
 * @brief	Order of opperations of a coder
 * 
 * @param	coder_void 
 * 			t_coder struct but casted as a void to pass to the thread
 * @return	void* 
 */
void			*coders_thread(void *coder_void);

/**
 * @brief 	Joins all the coder threads
 * 
 * @param	system
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->coders is an array pointing to all the coder threads 
 * 
 * 			system->nbr_coders_created and system->nbr->launched are counters
 * 			for how many structs to free and how many threads to join
 *
 * @return int 
 */
int				join_coders(t_system *system);

/**
 * @brief 	Releases all memory and destroys all mutexes and pthread_cond_t
 * 
 * @param	system 
 * 			The central struct storing all the inputted paramaters.
 * 			It also points to all the coders and dongles to ase in their
 * 			creation and destruction.
 * 
 * 			system->coders is an array pointing to all the coder threads 
 * 
 * 			system->nbr_coders_created and system->nbr->launched are counters
 * 			for how many structs to free and how many threads to join
 * 
 * 			system->dongles is an array pointing to all the dongles
 * 
 * 			system->nbr_dongles_created is to free accurate maount of dongles
 * 			created
 * 
 * @param	mode
 * 			Should it return 1 or 0
 *  
 * @return	int 
 * 			Returns the value set in mode or 1 if a case failed
 */
int				free_for_all(t_system *system, int mode);

/**
 * @brief	Get the dongles edf object
 * 			Implements edf schedule startegy
 * 
 * @param	coder 
 */
void			get_dongles_edf(t_coder *coder);

/**
 * @brief	Get the dongles fifo object
 * 			Implets fifo strategy
 * 
 * @param	coder 
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread.
 */
void			get_dongles_fifo(t_coder *coder);

/**
 * @brief 	Makes sur that a coder has two dongles. If combines output
 * 			to more likely scenarios.
 * 
 * @param	first
 * 			The first t_dongle a coder will take.
 * 
 * @param	second
 * 			The second t_dongle a coder will take.
 */
void			to_get_two(t_dongle *first, t_dongle *second);

/**
 * @brief 	Coder realeses a specific dongle
 * 
 * @param	coder 
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread.
 * 
 * @param	dongle 
 * 			A pointer to a dongle struct owned by coder
 */
void			release(t_coder *coder, t_dongle *dongle);

/**
 * @brief	All the necessary printing and waiting for dongles
 * 
 * @param	coder 
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread.
 * 
 * 			coder->time_to_compile is the time it should compile
 */
void			compilation_stage(t_coder *coder);

/**
 * @brief 	Prints the message and sleeps for time set by input paramaters
 * 
 * @param	coder 
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread.
 */
void			debugging_stage(t_coder *coder);

/**
 * @brief 	Prints the message and sleeps for time set by input paramaters
 * 
 * @param	coder 
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread.
 */
void			refactoring_stage(t_coder *coder);

/**
 * @brief 	When there is one coder
 * 
 * @param	coder
 * 			A pointer to a coder struct with all the attributes needed
 * 			for a coder thread.
 */
void			one_coder(t_coder *coder);

#endif