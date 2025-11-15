/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:28:38 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 21:11:51 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exec_dinner(t_program *data, int i)
{
	data->philo.id = i + 1;
	data->philo.last_meal = my_gettime();
	if (pthread_create(&data->philo.monitor, NULL, fork_monitor, data) == -1)
		exit_processes(data, 242);
	if (data->philo.id % 2 == 0)
		my_sleep(data, data->philo.time_to_eat / 2);
	while (check_finished(data) == 0)
	{
		ft_eat(data);
		ft_sleep(data);
		ft_think(data);
	}
	pthread_join(data->philo.monitor, NULL);
	exit_processes(data, data->philo.id);
}

void	ft_eat(t_program *data)
{
	sem_wait(data->forks);
	writer(data, "has taken a fork", data->philo.id);
	sem_wait(data->forks);
	writer(data, "has taken a fork", data->philo.id);
	sem_wait(data->eat_lock);
	data->philo.last_meal = my_gettime();
	sem_post(data->eat_lock);
	writer(data, "is eating", data->philo.id);
	my_sleep(data, data->philo.time_to_eat);
	sem_wait(data->eat_lock);
	data->philo.meals_count++;
	sem_post(data->eat_lock);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	ft_sleep(t_program *data)
{
	if (check_finished(data))
		return ;
	writer(data, "is sleeping", data->philo.id);
	my_sleep(data, data->philo.time_to_sleep);
}

void	ft_think(t_program *data)
{
	int	time;

	if ((data->amount % 2) == 0)
		return ;
	time = (2 * data->philo.time_to_eat) - data->philo.time_to_sleep;
	if (time < 0)
		time = 1;
	writer(data, "is thinking", data->philo.id);
	my_sleep(data, time);
}

int	one_philo(t_program *data)
{
	sem_wait(data->eat_lock);
	data->philo.last_meal = my_gettime();
	data->philo.id = 1;
	sem_post(data->eat_lock);
	writer(data, "has taken a fork", data->philo.id);
	while (my_gettime() - data->philo.last_meal < data->time_to_die)
		usleep(500);
	writer(data, "died", data->philo.id);
	return (0);
}
