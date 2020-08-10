/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_dir_usage_vm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:00:46 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:00:05 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			g_dir[17] = {T_DIR_SIZE,
	4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};

int			spell_dir_size(int type, int spell)
{
	if (type == REG)
		return (1);
	if (type == IND)
		return (2);
	if (type == DIR)
		return (g_dir[spell]);
	return (0);
}
