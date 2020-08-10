/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pos_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:59:22 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:03:53 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			calс_new_pos(int pos)
{
	if (pos >= MEM_SIZE)
		return (pos % MEM_SIZE);
	while (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

void		set_jump(t_serf *serf, int reg)
{
	if (reg != 0)
		serf->jump = 0;
	else
		serf->jump = 1;
}

int			find_num(t_virt *v, t_serf *serf, int pos, int size)
{
	char	dir[4];
	int		i;

	i = 0;
	while (i < size)
	{
		dir[size - i - 1] = v->map[calс_new_pos(serf->pos + pos + i)];
		i++;
	}
	if (size == 4)
		return (*((int *)dir));
	if (size == 2)
		return (*((short *)dir));
	if (size == 1)
		return (dir[0]);
	return (0);
}
