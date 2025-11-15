/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:30:35 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 20:38:38 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_processes(t_program *data, int flag)
{
	int	exit_flag;

	sem_wait(data->stop);
	if (data->philo.died)
		exit_flag = 255;
	else
		exit_flag = flag;
	sem_post(data->stop);
	sem_close(data->stop);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->eat_lock);
	free(data->pid);
	exit (exit_flag);
}

void	cleanup(t_program *data)
{
	free(data->pid);
	sem_close(data->stop);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->eat_lock);
	sem_unlink("/stop");
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eat_lock");
}

void	kill_old_forks(t_program *data, int i)
{
	while (i >= 0)
	{
		kill(data->pid[i], SIGKILL);
		i--;
	}
}
