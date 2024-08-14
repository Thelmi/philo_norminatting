/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:34:30 by thelmy            #+#    #+#             */
/*   Updated: 2024/08/14 18:03:16 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000LL) + (now.tv_usec / 1000));
}

int	print_status(t_philo **philo, double timestamp_in_ms, char *str)
{
	pthread_mutex_lock(&(*philo)->info->death_lock);
	if ((*philo)->info->dead == 1)
	{
		pthread_mutex_unlock(&(*philo)->info->death_lock);
		return (1);
	}
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	printf("%s%d %s%d %s%s\n", CYAN,
		(int)timestamp_in_ms, RED, (*philo)->philo, RESET, str);
	pthread_mutex_unlock(&(*philo)->info->death_lock);
	return (0);
}

void	one_philo(t_philo **philo, double timestamp_in_ms,
	long long started_meal)
{
	while ((int)((time_now() - (*philo)->info->time_bc)
		- started_meal) < ((*philo)->info->t2die))
		usleep(150);
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	printf("%d %d died\n", (int)timestamp_in_ms, (*philo)->philo);
}

int	death_check2(t_philo **philo, double timestamp_in_ms)
{
	pthread_mutex_lock(&(*philo)->info->death_lock);
	if ((*philo)->info->dead == 1)
	{
		pthread_mutex_unlock(&(*philo)->info->death_lock);
		return (1);
	}
	(*philo)->info->dead = 1;
	timestamp_in_ms = time_now() - (*philo)->info->time_bc;
	printf("%d %d died\n", (int)timestamp_in_ms, (*philo)->philo);
	pthread_mutex_unlock(&(*philo)->info->death_lock);
	return (1);
}

int	death_check(t_philo **philo, double timestamp_in_ms)
{
	long long	started_meal;

	started_meal = time_now() - (*philo)->info->time_bc;
	if ((*philo)->info->philos == 1)
	{
		one_philo(philo, timestamp_in_ms, started_meal);
		return (1);
	}
	pthread_mutex_lock(&(*philo)->info->death_lock);
	if ((*philo)->info->dead == 1)
	{
		pthread_mutex_unlock(&(*philo)->info->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->info->death_lock);
	if ((time_now() - (*philo)->info->time_bc)
		- (*philo)->last_meal > (*philo)->info->t2die)
	{
		death_check2(philo, timestamp_in_ms);
		return (1);
	}
	return (0);
}

void	fork_check(t_philo **philo, int *fork1, int *fork2)
{
	if ((*philo)->philo == 1)
	{
		(*fork1) = (*philo)->info->philos - 1;
		(*fork2) = (*philo)->philo - 1;
	}
	else
	{
		(*fork1) = (*philo)->philo - 2;
		(*fork2) = (*philo)->philo - 1;
	}
	if ((*fork1) < (*fork2))
	{
		pthread_mutex_lock(&(*philo)->info->fork_lock[(*fork1)]);
		pthread_mutex_lock(&(*philo)->info->fork_lock[(*fork2)]);
	}
	else
	{
		pthread_mutex_lock(&(*philo)->info->fork_lock[*fork2]);
		pthread_mutex_lock(&(*philo)->info->fork_lock[*fork1]);
	}
}

int eating_routine(t_philo **philo, double timestamp_in_ms, int fork1, int fork2)
{
	long long	started_meal;

	started_meal = 0;
	started_meal = time_now() - (*philo)->info->time_bc;
	while ((int)((time_now() - (*philo)->info->time_bc)
		- started_meal) < ((*philo)->info->t2eat))
	{
		if (death_check(philo, timestamp_in_ms))
		{
			pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
			pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
			return (1);
		}
		usleep(150);
	}
	return (0);
}

int	eating2(t_philo **philo, double timestamp_in_ms, int fork1, int fork2)
{
	// long long	started_meal;

	// started_meal = 0;
	if (print_status(philo, timestamp_in_ms, "has taken a fork")
		|| print_status(philo, timestamp_in_ms, "has taken a fork")
		|| print_status(philo, timestamp_in_ms, "is eating"))
	{
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
		return (1);
	}
	if (eating_routine(philo, timestamp_in_ms, fork1, fork2))
	{
		// pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
		// pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
		return (1);
	}
	// started_meal = time_now() - (*philo)->info->time_bc;
	// while ((int)((time_now() - (*philo)->info->time_bc)
	// 	- started_meal) < ((*philo)->info->t2eat))
	// {
	// 	if (death_check(philo, timestamp_in_ms))
	// 	{
	// 		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
	// 		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
	// 		return (1);
	// 	}
	// 	usleep(150);
	// }
	(*philo)->last_meal = time_now() - (*philo)->info->time_bc;
	pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
	pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
	if (print_status(philo, timestamp_in_ms, "blsa7a"))
		return (1);
	return (0);
}

int	eating(t_philo **philo, double timestamp_in_ms)
{
	int	fork1;
	int	fork2;

	while (1)
	{
		fork_check(philo, &fork1, &fork2);
		if ((*philo)->info->forks[fork2] != (*philo)->philo
			&& (*philo)->info->forks[fork1] != (*philo)->philo)
		{
			(*philo)->info->forks[fork1] = (*philo)->philo;
			(*philo)->info->forks[fork2] = (*philo)->philo;
			if (death_check(philo, timestamp_in_ms))
			{
				pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
				pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
				return (1);
			}
			if (eating2(philo, timestamp_in_ms, fork1, fork2))
				return (1);
			break ;
		}
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork2]);
		pthread_mutex_unlock(&(*philo)->info->fork_lock[fork1]);
	}
	return (0);
}

int	sleeping(t_philo **philo, double timestamp_in_ms)
{
	if (death_check(philo, timestamp_in_ms))
		return (1);
	if (print_status(philo, timestamp_in_ms, "is sleeping"))
		return (1);
	(*philo)->started_sleep = time_now() - (*philo)->info->time_bc;
	while ((time_now() - (*philo)->info->time_bc)
		- (*philo)->started_sleep < ((*philo)->info->t2sleep))
	{
		if (death_check(philo, timestamp_in_ms))
			return (1);
		usleep(150);
	}
	return (0);
}
