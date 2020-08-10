/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_decor_array_vm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:48:59 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:51:05 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		fill_decor_array4(t_opencl *o)
{
	o->decor[221] = true;
	o->decor[226] = true;
	o->decor[228] = true;
	o->decor[230] = true;
	o->decor[232] = true;
	o->decor[234] = true;
	o->decor[236] = true;
	o->decor[241] = true;
	o->decor[243] = true;
	o->decor[245] = true;
	o->decor[247] = true;
	o->decor[249] = true;
	o->decor[251] = true;
	o->decor[257] = true;
	o->decor[259] = true;
}

void		fill_decor_array3(t_opencl *o)
{
	o->decor[139] = true;
	o->decor[140] = true;
	o->decor[166] = true;
	o->decor[170] = true;
	o->decor[181] = true;
	o->decor[185] = true;
	o->decor[187] = true;
	o->decor[188] = true;
	o->decor[189] = true;
	o->decor[191] = true;
	o->decor[192] = true;
	o->decor[193] = true;
	o->decor[196] = true;
	o->decor[200] = true;
	o->decor[202] = true;
	o->decor[204] = true;
	o->decor[206] = true;
	o->decor[211] = true;
	o->decor[213] = true;
	o->decor[215] = true;
	o->decor[217] = true;
	o->decor[218] = true;
	o->decor[219] = true;
	fill_decor_array4(o);
}

void		fill_decor_array2(t_opencl *o)
{
	o->decor[78] = true;
	o->decor[80] = true;
	o->decor[82] = true;
	o->decor[86] = true;
	o->decor[87] = true;
	o->decor[88] = true;
	o->decor[91] = true;
	o->decor[93] = true;
	o->decor[95] = true;
	o->decor[97] = true;
	o->decor[101] = true;
	o->decor[106] = true;
	o->decor[108] = true;
	o->decor[109] = true;
	o->decor[110] = true;
	o->decor[112] = true;
	o->decor[116] = true;
	o->decor[117] = true;
	o->decor[118] = true;
	o->decor[121] = true;
	o->decor[136] = true;
	o->decor[137] = true;
	o->decor[138] = true;
	fill_decor_array3(o);
}

void		fill_decor_array(t_opencl *o)
{
	o->decor[16] = true;
	o->decor[17] = true;
	o->decor[18] = true;
	o->decor[19] = true;
	o->decor[20] = true;
	o->decor[31] = true;
	o->decor[46] = true;
	o->decor[48] = true;
	o->decor[49] = true;
	o->decor[50] = true;
	o->decor[52] = true;
	o->decor[53] = true;
	o->decor[54] = true;
	o->decor[56] = true;
	o->decor[57] = true;
	o->decor[58] = true;
	o->decor[61] = true;
	o->decor[63] = true;
	o->decor[65] = true;
	o->decor[67] = true;
	o->decor[71] = true;
	o->decor[73] = true;
	o->decor[76] = true;
	fill_decor_array2(o);
}
