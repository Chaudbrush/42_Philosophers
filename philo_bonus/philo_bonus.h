/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:48:44 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 21:14:19 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef unsigned long		t_ulong;

typedef struct s_philo
{
	int			id;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_total;
	int			meals_count;
	int			full;
	int			stop;
	int			exit;
	int			died;
	t_ulong		last_meal;
	pthread_t	monitor;
}	t_philo;

typedef struct s_program
{
	int			amount;
	int			dead_philo;
	pid_t		*pid;
	t_philo		philo;
	t_ulong		time_to_die;
	t_ulong		start_simulation;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*stop;
	sem_t		*eat_lock;
}	t_program;

// Data Init
int		philos_init(t_program *data);
int		init_semaphore(t_program *data);
int		data_init(int *args, t_program *data);
void	abort_semaphore(t_program *data, int flag);

// Exec utils
t_ulong	my_gettime(void);
void	printer(t_ulong time, int id, char *str);
void	writer(t_program *data, char *str, int i);
void	my_sleep(t_program *data, t_ulong target_time);
void	num_to_buffer(char *buffer, t_ulong num, int *index);

// Exit and Error
void	cleanup(t_program *data);
void	kill_old_forks(t_program *data, int i);
void	exit_processes(t_program *data, int flag);

// Monitor
void	*fork_monitor(void *data);
int		check_finished(t_program *data);
void	monitor_change(t_program *data, int flag);

// Parent Utils
int		handle_wait(t_program *data);
void	kill_processes(t_program *data);
void	handle_death(t_program *data, int id);

// Parse
int		mod_atoi(char *str);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		parse_args(char **av, int *args);

// Simulation
void	ft_eat(t_program *data);
void	ft_sleep(t_program *data);
void	ft_think(t_program *data);
int		one_philo(t_program *data);
void	exec_dinner(t_program *data, int i);

#endif
