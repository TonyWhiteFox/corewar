/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_visual_vm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:50:37 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 19:05:27 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		heat_cl_bufers(t_opencl *o, int temp)
{
	temp = MEM_SIZE;
	if (!(o->ret_pic = (cl_int *)malloc(sizeof(cl_int) * o->win_size)))
		memory_error();
	o->mem_picture = clCreateBuffer(o->context, CL_MEM_READ_WRITE, o->win_size *
				sizeof(cl_int), NULL, &o->ret);
	o->mem_map = clCreateBuffer(o->context, CL_MEM_READ_ONLY, temp *
				sizeof(cl_uchar), NULL, &o->ret);
	o->mem_log = clCreateBuffer(o->context, CL_MEM_READ_ONLY, temp *
				sizeof(cl_uint), NULL, &o->ret);
	o->mem_serf = clCreateBuffer(o->context, CL_MEM_READ_ONLY, temp *
				sizeof(bool), NULL, &o->ret);
	o->mem_live = clCreateBuffer(o->context, CL_MEM_READ_ONLY, temp *
				sizeof(cl_uint), NULL, &o->ret);
	o->mem_decor = clCreateBuffer(o->context, CL_MEM_READ_ONLY, 285 *
				sizeof(bool), NULL, &o->ret);
}

void		heat_cl_kernel(t_opencl *o)
{
	int		fd;
	char	*temp1;
	char	*temp2;
	int		j;

	fd = open("src/opencl/paint_map.cl", O_RDONLY);
	o->file = ft_strnew(1);
	while ((j = get_next_line(fd, &temp1)))
	{
		temp2 = o->file;
		o->file = ft_strjoin(o->file, temp1);
		free(temp1);
		free(temp2);
	}
	close(fd);
}

void		heat_opencl(t_opencl *o, t_virt *v)
{
	o->ret = clGetPlatformIDs(1, &o->platform_id, &o->ret_num_platforms);
	o->ret = clGetDeviceIDs(o->platform_id, CL_DEVICE_TYPE_GPU, 1,
				&o->device_id, &o->ret_num_devices);
	o->context = clCreateContext(NULL, 1, &o->device_id, NULL, NULL, &o->ret);
	o->command_queue = clCreateCommandQueue(o->context,
				o->device_id, 0, &o->ret);
	heat_cl_kernel(o);
	o->kernel_size = ft_strlen(o->file);
	o->program = clCreateProgramWithSource(o->context, 1,
			(const char **)&o->file, (const size_t *)&o->kernel_size, &o->ret);
	o->ret = clBuildProgram(o->program, 1, &o->device_id, NULL, NULL, NULL);
	o->kernel = clCreateKernel(o->program, "kercorewar", &o->ret);
	o->win_size = v->w_x * v->w_y;
	heat_cl_bufers(o, 0);
}

void		heat_mlx(t_mlx *mlx, t_virt *v)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, v->w_x, v->w_y, "CoreWar");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, v->w_x, v->w_y);
	mlx->img_adr = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
					&mlx->stride, &mlx->endian);
	mlx->stop = false;
	mlx->bpp /= 8;
	mlx->cycle_per_frame = 1;
	mlx->sleep_after_frame = 0;
	mlx->stop = false;
}

void		heat_visual(t_virt *v)
{
	if (!(v->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		memory_error();
	if (!(v->opencl = (t_opencl *)malloc(sizeof(t_opencl))))
		memory_error();
	v->w_x = 1792;
	v->w_y = 1024;
	if (!(v->opencl->decor = (bool *)malloc(sizeof(bool) * 285)))
		memory_error();
	ft_bzero(v->opencl->decor, sizeof(bool) * 285);
	fill_decor_array(v->opencl);
	v->opencl->flows = MEM_SIZE * 2;
	heat_opencl(v->opencl, v);
	heat_mlx(v->mlx, v);
}
