/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:48:44 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/08 22:01:29 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long		t_ulong;
typedef pthread_mutex_t		t_mutex;
typedef struct s_program	t_program;

typedef struct s_philos
{
	int			philo_id;
	pthread_t	thread;
	t_mutex		*right_fork;
	t_mutex		*left_fork;
	int			meals_count;
	int			meals_total;
	int			time_to_eat;
	int			time_to_sleep;
	t_ulong		last_meal;
	t_program	*data;
}	t_philos;

typedef struct s_program
{
	int			amount;
	int			force_stop;
	int			wait_start;
	t_ulong		start_simulation;
	t_philos	*ph;
	t_mutex		*forks;
	t_mutex		print_lock;
	t_mutex		eat_lock;
	t_mutex		stop;
	t_ulong		time_to_die;
	pthread_t	monitor;
}	t_program;

// DELETE ?
void	clean_mutex(t_program *data, int i, int flag);
void	wait_all_philos(t_philos *philo);

// Data Init
int		mutex_init(t_program *data);
int		join_threads(t_program *data);
int		start_simulation(t_program *data);
int		data_init(int *args, t_program *data);
void	philos_init(int *args, t_program *data);

// Exec utils
t_ulong	my_gettime(void);
void	printer(t_ulong time, int id, char *str);
void	writer(t_program *data, char *str, int i);
void	my_sleep(t_program *data, t_ulong target_time);
void	num_to_buffer(char *buffer, t_ulong num, int *index);

// Lib Helpers
int		mod_atoi(char *str);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);

// Monitoring
void	*ft_monitoring(void *data);
int		check_finished(t_program *data);
void	handle_death(t_program *prog, int i);
int		should_finish(t_program *prog, int i, int full);

// Parse and Free
void	cleanup(t_program *data);
int		parse_args(char **av, int *args);

// Simulation
void	*dinner(void *data);
void	*one_philo(void *data);
void	ft_eat(t_philos *philo);
void	ft_sleep(t_philos *philo);
void	ft_think(t_philos *philo);

#endif
