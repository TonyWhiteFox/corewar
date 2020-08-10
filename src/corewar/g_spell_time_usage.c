/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_spell_time_usage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:09:42 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:44:20 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			g_spell_time[17] = {PRICE, 10, 5, 5, 10, 10, 6,
	6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

void		make_a_move(t_virt *v, t_serf *serf)
{
	while (serf)
	{
		if (serf->left_to_cust == 0)
		{
			serf->spell = v->map[serf->pos];
			if (serf->spell > 0 && serf->spell <= MAX_OPS)
				serf->left_to_cust = g_spell_time[serf->spell];
			else
				serf->left_to_cust = -1;
		}
		multi_cust(v, serf);
		v->have_serf[serf->pos] = TRUE;
		v->serfs_live[serf->creater_no] += 1;
		serf = serf->next;
	}
}
