/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:48:30 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 15:03:54 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(int *args, t_program *data)
{
	data->ph = malloc(sizeof(t_philos) * args[0]);
	if (!data->ph)
		return (1);
	data->forks = malloc(sizeof(t_mutex) * args[0]);
	if (!data->forks)
		return (free(data->ph), 1);
	data->force_stop = 0;
	data->wait_start = 0;
	data->amount = args[0];
	data->time_to_die = args[1];
	philos_init(args, data);
	if (mutex_init(data))
	{
		ft_putstr_fd("-error: Failed init\n", 2);
		return (1);
	}
	return (0);
}

void	philos_init(int *args, t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->amount)
	{
		data->ph[i].philo_id = i + 1;
		if (data->ph[i].philo_id % 2)
		{
			data->ph[i].right_fork = &data->forks[i];
			data->ph[i].left_fork = &data->forks[(i + 1) % data->amount];
		}
		else
		{
			data->ph[i].right_fork = &data->forks[(i + 1) % data->amount];
			data->ph[i].left_fork = &data->forks[i];
		}
		data->ph[i].meals_count = 0;
		data->ph[i].meals_total = args[4];
		data->ph[i].time_to_eat = args[2];
		data->ph[i].time_to_sleep = args[3];
		data->ph[i].data = data;
	}
}

int	mutex_init(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (clean_mutex(data, i, 0), 1);
		i++;
	}
	if (pthread_mutex_init(&data->eat_lock, NULL))
		return (clean_mutex(data, i, 0), 1);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (clean_mutex(data, i, 1), 1);
	if (pthread_mutex_init(&data->stop, NULL))
		return (clean_mutex(data, i, 2), 1);
	return (0);
}

int	start_simulation(t_program *data)
{
	int	i;

	data->start_simulation = my_gettime();
	i = -1;
	if (data->amount == 1)
	{
		data->ph[0].last_meal = data->start_simulation;
		if (pthread_create(&data->ph[0].thread, NULL, one_philo, &data->ph[0]))
			return (1);
	}
	else
	{
		while (++i < data->amount)
		{
			data->ph[i].last_meal = data->start_simulation;
			if (pthread_create(&data->ph[i].thread, NULL, dinner, &data->ph[i]))
				return (1);
		}
	}
	data->wait_start = 1;
	if (pthread_create(&data->monitor, NULL, ft_monitoring, data))
		return (1);
	if (join_threads(data))
		return (1);
	return (0);
}

int	join_threads(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->amount)
	{
		if (pthread_join(data->ph[i].thread, NULL))
			return (1);
	}
	if (pthread_join(data->monitor, NULL))
		return (1);
	return (0);
}
