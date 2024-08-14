/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:17 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/14 16:56:28 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo **philo, double timestamp_in_ms)
{
	if (print_status(philo, timestamp_in_ms, "is thinking"))
		return (1);
	return (0);
}

void	*life(void *philo_num)
{
	long long	timestamp_in_ms;
	t_philo		*philo;
	int			i;

	philo = (t_philo *)philo_num;
	timestamp_in_ms = 0;
	if (philo->info->philos != 1 && philo->philo % 2 == 1)
		usleep (250);
	if (philo->info->philos == 1)
	{
		death_check(&philo, timestamp_in_ms);
		return (NULL);
	}
	i = 0;
	if (philo->info->meals != -1)
	{
		while (i < philo->info->meals)
		{
			if (eating(&philo, timestamp_in_ms))
			{
				if (philo)
					free(philo);
				return (NULL);
			}
			if (i == philo->info->meals - 1)
				break ;
			if (sleeping(&philo, timestamp_in_ms))
			{
				if (philo)
					free(philo);
				return (NULL);
			}
			if (thinking(&philo, timestamp_in_ms))
			{
				if (philo)
					free(philo);
				return (NULL);
			}
			i++;
		}
	}
	else
	{
		while (1)
		{
			if (eating(&philo, timestamp_in_ms)
				|| sleeping(&philo, timestamp_in_ms)
				|| thinking(&philo, timestamp_in_ms))
			{
				if (philo)
					free(philo);
				return (NULL);
			}
		}
	}
	if (philo)
		free(philo);
	return (NULL);
}

int	creating_threads(pthread_t	*threads, t_info *info, t_philo		*philo)
{
	int i;
	
	i = 0;
	while (i < 200)
	{
		pthread_mutex_init(&info->fork_lock[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->philos)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (0);
		initializer(philo, info, i);
		if (pthread_create(&threads[i], NULL, life, (void *)philo))
			return (0);
		i++;
	}
	return (1);
}

int	execution(t_info *info)
{
	pthread_t	threads[200];
	t_philo		*philo;
	int			i;

	philo = NULL;
	pthread_mutex_init(&info->death_lock, NULL);
	pthread_mutex_init(&info->print_lock, NULL);
	i = 0;
	info->time_bc = time_now();
	if (!creating_threads(threads, info, philo))
		return (0);
	while (i < info->philos)
	{
		if (pthread_join(threads[i], NULL))
			return (0);
		i++;
	}
	i = 0;
	while (i < 200)
	{
		pthread_mutex_destroy(&info->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->print_lock);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (!(parsing(ac, av, &info)))
		return (1);
	if (!(execution(&info)))
		return (1);
	return (0);
}
