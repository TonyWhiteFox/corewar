/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extermination_serfs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:11:36 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:01:45 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_serf		*find_heir(t_virt *v, t_serf *temp1, t_serf *temp2)
{
	if (v->serf == temp1)
	{
		v->serf = temp1->next;
		free(temp1->reg);
		free(temp1);
		return (v->serf);
	}
	else
	{
		temp2->next = temp1->next;
		free(temp1->reg);
		free(temp1);
		return (temp2->next);
	}
	return (NULL);
}

void		kill_serf(t_virt *v, t_serf *temp1, t_serf *temp2)
{
	while (temp1)
	{
		if (v->total_cycles - temp1->last_live_cycle >= v->cycles_before_die)
			temp1 = find_heir(v, temp1, temp2);
		else
		{
			temp2 = temp1;
			temp1 = temp1->next;
		}
	}
}

void		extermination_serfs(t_virt *v)
{
	v->without_abbreviations++;
	kill_serf(v, v->serf, v->serf);
	if (v->hardcore)
		v->cycles_before_die = 1200;
	else if (v->life_in_die_cycle >= NBR_LIVE)
	{
		v->cycles_before_die -= CYCLE_DELTA;
		v->without_abbreviations = 0;
	}
	else if (v->without_abbreviations >= MAX_CHECKS)
	{
		v->cycles_before_die -= CYCLE_DELTA;
		v->without_abbreviations = 0;
	}
	v->life_in_die_cycle = 0;
	v->cycles = 0;
}
