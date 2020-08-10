/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cl_vm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:16:08 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 15:02:44 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		send_argument_to_cl_add(t_virt *v, t_opencl *o, cl_int tmp_int)
{
	v->alter_total_cycles++;
	o->ret = clSetKernelArg(o->kernel, 17, sizeof(cl_int),
							&v->alter_total_cycles);
	if (v->mlx->stop)
		tmp_int = 1;
	else
		tmp_int = 0;
	o->ret = clSetKernelArg(o->kernel, 18, sizeof(cl_int), &tmp_int);
	if (v->is_end)
		tmp_int = 1;
	else
		tmp_int = 0;
	o->ret = clSetKernelArg(o->kernel, 19, sizeof(cl_int), &tmp_int);
}

void		send_argument_to_cl(t_virt *v, t_opencl *o, cl_int tmp_int)
{
	send_memory_buffers_to_cl(v, o);
	tmp_int = (cl_int)o->flows;
	o->ret = clSetKernelArg(o->kernel, 8, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->cycles_before_die;
	o->ret = clSetKernelArg(o->kernel, 9, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->mlx->cycle_per_frame;
	o->ret = clSetKernelArg(o->kernel, 10, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->mlx->sleep_after_frame;
	o->ret = clSetKernelArg(o->kernel, 11, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->player_num_last_say_life;
	o->ret = clSetKernelArg(o->kernel, 12, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->serfs_live[1];
	o->ret = clSetKernelArg(o->kernel, 13, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->serfs_live[2];
	o->ret = clSetKernelArg(o->kernel, 14, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->serfs_live[3];
	o->ret = clSetKernelArg(o->kernel, 15, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->serfs_live[4];
	o->ret = clSetKernelArg(o->kernel, 16, sizeof(cl_int), &tmp_int);
	send_argument_to_cl_add(v, o, tmp_int);
	execute_cl(o, v->mlx);
}

void		send_memory_buffers_to_cl2(t_virt *v, t_opencl *o)
{
	cl_int	tmp_int;

	o->ret = clSetKernelArg(o->kernel, 0, sizeof(cl_mem),
							(void *)&o->mem_picture);
	o->ret = clSetKernelArg(o->kernel, 1, sizeof(cl_mem),
							(void *)&o->mem_map);
	o->ret = clSetKernelArg(o->kernel, 2, sizeof(cl_mem),
							(void *)&o->mem_log);
	o->ret = clSetKernelArg(o->kernel, 3, sizeof(cl_mem),
							(void *)&o->mem_serf);
	o->ret = clSetKernelArg(o->kernel, 4, sizeof(cl_mem),
							(void *)&o->mem_live);
	o->ret = clSetKernelArg(o->kernel, 5, sizeof(cl_mem),
							(void *)&o->mem_decor);
	tmp_int = (cl_int)v->w_x;
	o->ret = clSetKernelArg(o->kernel, 6, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->total_cycles;
	o->ret = clSetKernelArg(o->kernel, 7, sizeof(cl_int), &tmp_int);
}

void		send_memory_buffers_to_cl(t_virt *v, t_opencl *o)
{
	cl_int	tmp_int;

	tmp_int = MEM_SIZE;
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
			o->win_size * sizeof(cl_int), o->ret_pic, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_map, CL_TRUE, 0,
			tmp_int * sizeof(cl_uchar), v->map, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_log, CL_TRUE,
			0, tmp_int * sizeof(cl_uint), v->log, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_serf, CL_TRUE,
			0, tmp_int * sizeof(bool), v->have_serf, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_live, CL_TRUE,
			0, tmp_int * sizeof(cl_int), v->live_log, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_decor, CL_TRUE,
			0, 285 * sizeof(bool), o->decor, 0, NULL, NULL);
	send_memory_buffers_to_cl2(v, o);
}

void		execute_cl(t_opencl *o, t_mlx *ml)
{
	size_t	i;

	i = o->flows + 1024;
	o->ret = clEnqueueNDRangeKernel(o->command_queue, o->kernel, 1, NULL,
									&i, NULL, 0, NULL, NULL);
	o->ret = clEnqueueReadBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
			o->win_size * sizeof(cl_int), o->ret_pic, 0, NULL, NULL);
	i = 0;
	while (i < o->win_size)
	{
		*(int *)(ml->img_adr + i * 4) = o->ret_pic[i];
		i++;
	}
	mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
}
