/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:34:50 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 20:43:27 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	data_init(int *args, t_program *data)
{
	data->pid = malloc(sizeof(pid_t) * args[0]);
	if (!data->pid)
		return (free(data), 1);
	data->amount = args[0];
	data->time_to_die = args[1];
	data->philo.time_to_eat = args[2];
	data->philo.time_to_sleep = args[3];
	data->philo.meals_total = args[4];
	data->philo.meals_count = 0;
	data->philo.full = 0;
	data->philo.stop = 0;
	data->philo.exit = 0;
	data->dead_philo = 0;
	data->philo.died = 0;
	if (init_semaphore(data))
	{
		ft_putstr_fd("-error: Failed init\n", 2);
		return (1);
	}
	data->start_simulation = my_gettime();
	return (0);
}

int	init_semaphore(t_program *data)
{
	sem_unlink("/stop");
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eat_lock");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->amount);
	if (data->forks == SEM_FAILED)
		return (1);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (abort_semaphore(data, 0), 1);
	data->stop = sem_open("/stop", O_CREAT, 0644, 1);
	if (data->stop == SEM_FAILED)
		return (abort_semaphore(data, 1), 1);
	data->eat_lock = sem_open("/eat_lock", O_CREAT, 0644, 1);
	if (data->eat_lock == SEM_FAILED)
		return (abort_semaphore(data, 2), 1);
	return (0);
}

int	philos_init(t_program *data)
{
	int	i;

	i = 0;
	if (data->amount == 1)
		return (one_philo(data));
	while (i < data->amount)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			kill_old_forks(data, i);
			cleanup(data);
			exit(1);
		}
		if (data->pid[i] == 0)
			exec_dinner(data, i);
		i++;
	}
	handle_wait(data);
	return (0);
}

void	abort_semaphore(t_program *data, int flag)
{
	if (flag == 0)
		sem_close(data->forks);
	else if (flag == 1)
	{
		sem_close(data->forks);
		sem_close(data->print);
	}
	else if (flag == 2)
	{
		sem_close(data->forks);
		sem_close(data->print);
		sem_close(data->stop);
	}
	else
		return ;
}
