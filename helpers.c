/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:02:04 by thelmy            #+#    #+#             */
/*   Updated: 2024/08/14 16:25:13 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initializer(t_philo *philo, t_info *info, int i)
{
	philo->total_meals = 0;
	philo->last_meal = 0;
	philo->philo = i + 1;
	philo->info = info;
}

int	destroyer(t_info *info)
{
	int	i;

	i = 0;
	while (i < 200)
	{
		if (pthread_mutex_destroy(&info->fork_lock[i]))
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&info->death_lock))
		return (0);
	if (pthread_mutex_destroy(&info->print_lock))
		return (0);
	return (1);
}
