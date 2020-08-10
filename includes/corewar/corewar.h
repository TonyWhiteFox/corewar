/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:51:18 by lshellie          #+#    #+#             */
/*   Updated: 2020/07/11 15:01:12 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _COREWAR_H
# define _COREWAR_H
# include "libft.h"
# include "mlx.h"
# define CL_SILENCE_DEPRECATION
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define AFF_OP 1
# define LLD_READ_SIZE 2
# define LIVE 1
# define LD 2
# define ST 3
# define ADD 4
# define SUB 5
# define AND 6
# define OR 7
# define XOR 8
# define ZJMP 9
# define LDI 10
# define STI 11
# define FORK 12
# define LLD 13
# define LLDI 14
# define LFORK 15
# define AFF 16

# define MAX_OPS 16

# define DIR 1
# define REG 2
# define IND 3

# define NUM_ARG 0
# define T_DIR_SIZE 5
# define PRICE 6

# define MEM_SIZE (4*1024)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define NBR_LIVE 21
# define MAX_CHECKS 10
# define CYCLE_DELTA 50
# define MAX_PLAYERS 4
# define CYCLE_TO_DIE 1536
# define IDX_MOD (MEM_SIZE / 8)
# define REG_NUMBER 16

typedef struct			s_opencl
{
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_context			context;
	cl_mem				mem_picture;
	cl_mem				mem_map;
	cl_mem				mem_log;
	cl_mem				mem_serf;
	cl_mem				mem_live;
	cl_mem				mem_decor;
	cl_command_queue	command_queue;
	int					ret;
	cl_int				*ret_pic;
	cl_int				flows;
	bool				*decor;
	char				*file;
	size_t				win_size;
	size_t				kernel_size;
}						t_opencl;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*img_adr;
	int					bpp;
	int					stride;
	int					endian;
	int					cycle_per_frame;
	int					sleep_after_frame;
	bool				stop;
}						t_mlx;

typedef struct			s_serf
{
	int					*reg;
	long unsigned int	id;
	int					pos;
	bool				jump;
	int					spell;
	int					left_to_cust;
	int					last_live_cycle;
	short int			creater_no;
	struct s_serf		*next;
}						t_serf;

typedef struct			s_gamer
{
	int					num;
	char				*name;
	char				*comment;
	int					size;
	char				*code;
	struct s_gamer		*next;
}						t_gamer;

typedef struct			s_option
{
	int					total_len;
	int					*var_type;
	int					*var_len;
	int					*variable;
}						t_option;

typedef struct			s_virt
{
	t_gamer				*gamer;
	t_serf				*serf;
	t_mlx				*mlx;
	t_opencl			*opencl;
	t_option			*option;
	cl_uchar			*map;
	cl_uint				*log;
	bool				*have_serf;
	cl_int				*live_log;
	cl_int				*serfs_live;
	long unsigned int	last_serf_id;
	int					total_gamers;
	short				w_x;
	short				w_y;
	int					total_cycles;
	cl_int				alter_total_cycles;
	int					cycles;
	int					life_in_die_cycle;
	int					cycles_before_die;
	short				without_abbreviations;
	int					player_num_last_say_life;
	bool				is_end;
	bool				show_winner;
	cl_int				temp;
	int					fd;
	int					d;
	int					dump;
	int					number;
	bool				vis;
	bool				hardcore;
}						t_virt;

void					check_program_args(int ac, char **av, t_virt *v, int i);
int						find_vis_or_dumps(int ac, char **av, t_virt *v, int i);

int						find_player(int ac, char **av, t_virt *v, int i);
void					check_format(char *av, int i);
void					read_gamers(char *av, t_virt *v);

void					create_gamer_and_fill_him(t_virt *v,
							t_gamer *new_gamer, t_gamer *temp_gamer);
int						get_int_in_fd(t_virt *v, int i, int tmp_int,
							unsigned char tmp_ch);
void					read_name(t_virt *v, t_gamer *new_gamer);
void					skip_empty(t_virt *v, int i, char tmp_ch);

void					read_size(t_virt *v, t_gamer *new_gamer);
void					read_comment(t_virt *v, t_gamer *new_gamer);
void					read_body(t_virt *v, t_gamer *new_gamer,
							int readed_byte, char test_for_read);

void					fill_decor_array(t_opencl *o);
void					fill_decor_array2(t_opencl *o);
void					fill_decor_array3(t_opencl *o);
void					fill_decor_array4(t_opencl *o);

void					heat_visual(t_virt *v);
void					heat_mlx(t_mlx *mlx, t_virt *v);
void					heat_opencl(t_opencl *o, t_virt *v);
void					heat_cl_kernel(t_opencl *o);
void					heat_cl_bufers(t_opencl *o, int temp);

void					send_gamers(t_virt *v);
void					get_start_pos_and_first_serf(t_virt *v, t_gamer *gamer,
							int start_pos, int i);
void					create_serf(t_virt *v, t_serf *surf, int i);
void					memory_error();

void					find_last_negative_player(t_virt *v, t_gamer *gamer,
								t_gamer *temp);
int						find_empty_num(t_virt *v, t_gamer *gamer, int numb,
							int temp);
void					get_all_number_for_gamers(t_gamer *gamer);
void					gamer_buble_sorting(t_virt *v, t_gamer *first_cycle,
							t_gamer *second_cycle, t_gamer *temp);
t_gamer					*gamer_swap(t_gamer *swap_now, t_gamer *swap_next,
							t_gamer *swap_prew, t_virt *v);

void					gamer_on_show(t_gamer *gamer);
void					init_start_params(t_virt *v);
void					init_start_params2(t_virt *v);
void					close_fd_send_error_close(t_virt *v, char *error_text);

int						find_num(t_virt *v, t_serf *serf, int pos, int size);
void					set_jump(t_serf *serf, int reg);
int						calс_new_pos(int pos);

int						spell_dir_size(int type, int spell);

void					calc_option_len(t_serf *serf, t_option *option, int i);
bool					check_valid_reg(t_serf *serf, t_option *option, int i);
bool					check_var_types(t_serf *serf, t_option *option);

void					make_a_move(t_virt *v, t_serf *serf);

void					extermination_serfs(t_virt *v);
void					kill_serf(t_virt *v, t_serf *temp1, t_serf *temp2);
t_serf					*find_heir(t_virt *v, t_serf *temp1, t_serf *temp2);

void					spell_book_with_vars(t_virt *v, t_serf *serf,
							t_option *option);
void					spell_book(t_virt *v, t_serf *serf);
void					multi_cust(t_virt *v, t_serf *serf);
void					dump_map(t_virt *v, int i, int dump);
void					hide_show_run(t_virt *v);

void					send_argument_to_cl_add(t_virt *v, t_opencl *o,
							cl_int tmp_int);
void					send_argument_to_cl(t_virt *v, t_opencl *o,
							cl_int tmp_int);
void					send_memory_buffers_to_cl2(t_virt *v, t_opencl *o);
void					send_memory_buffers_to_cl(t_virt *v, t_opencl *o);
void					execute_cl(t_opencl *o, t_mlx *ml);

void					hardcore_mode(t_virt *v, int i);
void					start_fight_vis2(t_virt *v, int size_mem,
							int player_max);
int						start_fight_vis(t_virt *v);
void					let_the_show_begin(t_virt *v);

void					winner_is(t_virt *v, t_gamer *gamer);
int						say_good_buy(t_virt *v);
int						key_press(int key, t_virt *v);

void					make_ldi(t_virt *v, t_serf *serf, t_option *option,
							int save_var);
void					make_aff(t_serf *serf, t_option *option);
void					make_st(t_virt *v, t_serf *serf, t_option *option);
void					make_sti(t_virt *v, t_serf *serf, t_option *option,
							int save_var);

void					make_and_or_xor(t_serf *serf, t_option *option,
							int save_var);
void					make_add_sub(t_serf *serf, t_option *option);
void					make_ld(t_serf *serf, t_option *option);

void					write_reg(t_serf *serf, t_option *option, int i);
void					fill_vars(t_virt *v, t_serf *serf, t_option *o, int i);
bool					clean_fill_check_option(t_virt *v, t_serf *serf,
							unsigned char temp_ch);
void					change_map(t_virt *v, t_serf *serf, int reg,
							int copy_in_pos);

void					make_fork(t_virt *v, t_serf *serf, int i, int dir);
void					make_zjmp(t_virt *v, t_serf *serf, int t_dir);
void					make_live(t_virt *v, t_serf *serf, int i, int t_dir);

#endif
