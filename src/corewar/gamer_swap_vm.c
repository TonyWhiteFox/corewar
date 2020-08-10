/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamer_swap_vm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:55:14 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:37:52 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_gamer		*gamer_swap(t_gamer *swap_now, t_gamer *swap_next,
					t_gamer *swap_prew, t_virt *v)
{
	if (swap_now == v->gamer)
		v->gamer = swap_next;
	else
		swap_prew->next = swap_next;
	swap_now->next = swap_next->next;
	swap_next->next = swap_now;
	return (swap_next);
}

void		gamer_buble_sorting(t_virt *v, t_gamer *first_cycle,
							t_gamer *second_cycle, t_gamer *temp)
{
	while (first_cycle->next)
	{
		second_cycle = v->gamer;
		while (second_cycle->next)
		{
			if (second_cycle->next->num > v->total_gamers ||
					second_cycle->num > v->total_gamers)
				exit(ft_printf("Maximal player num = sum players!\n"));
			if (second_cycle->num == second_cycle->next->num)
				exit(ft_printf("Duplicate player num!\n"));
			if (second_cycle->num > second_cycle->next->num)
			{
				second_cycle = gamer_swap(second_cycle,
							second_cycle->next, temp, v);
				first_cycle = v->gamer;
			}
			temp = second_cycle;
			second_cycle = second_cycle->next;
		}
		first_cycle = first_cycle->next;
	}
}

void		get_all_number_for_gamers(t_gamer *gamer)
{
	while (gamer->next)
	{
		gamer->num *= -1;
		gamer = gamer->next;
	}
}

int			find_empty_num(t_virt *v, t_gamer *gamer, int numb, int temp)
{
	while (numb <= v->total_gamers)
	{
		while (gamer)
		{
			if (numb < gamer->num)
				return (numb);
			if (numb == gamer->num)
			{
				numb++;
				temp = gamer->num;
				gamer = gamer->next;
			}
			if (!gamer && numb <= v->total_gamers)
				return (numb);
		}
		if (numb < temp)
			return (numb);
		else
			numb++;
	}
	return (0);
}

void		find_last_negative_player(t_virt *v, t_gamer *gamer,
								t_gamer *temp)
{
	bool	is_find;

	is_find = FALSE;
	while (gamer->next && !is_find)
	{
		if (gamer->next->num > 0)
			is_find = TRUE;
		else
			gamer = gamer->next;
	}
	if (!is_find)
		get_all_number_for_gamers(v->gamer);
	else
	{
		temp = gamer->next;
		gamer->num = find_empty_num(v, temp, 1, 0);
	}
}
