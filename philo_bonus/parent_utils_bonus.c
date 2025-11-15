/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:37:09 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 18:18:55 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
}

int	handle_wait(t_program *data)
{
	int	i;
	int	exit_flag;

	i = 0;
	while (i < data->amount)
	{
		waitpid(-1, &exit_flag, 0);
		if (WEXITSTATUS(exit_flag) == 255)
		{
			i++;
			continue ;
		}
		else if (WEXITSTATUS(exit_flag) == 242)
		{
			kill_processes(data);
			ft_putstr_fd("-error: Failed init\n", 2);
			cleanup(data);
			exit (1);
		}
		else if (WEXITSTATUS(exit_flag) < data->amount)
			handle_death(data, WEXITSTATUS(exit_flag));
		i++;
	}
	return (0);
}

void	handle_death(t_program *data, int id)
{
	if (data->dead_philo)
		return ;
	data->dead_philo = 1;
	sem_wait(data->print);
	printer(my_gettime() - data->start_simulation, id, "died");
	kill_processes(data);
	sem_post(data->print);
}
