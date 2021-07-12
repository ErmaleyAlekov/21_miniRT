#ifndef MINI_RT_H
# define MINI_RT_H
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# define EPSILON 0.0000001f

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_save_data
{
	double		a;
	double		b;
	double		c;
	double		radius;
	t_vec		pos1;
}	t_save;

typedef struct s_light
{
	t_vec			pos;
	double			intensity;
	t_color			color;
	t_save			save;
	struct s_light	*next;
}	t_light;

typedef struct s_ray
{
	t_vec	start;
	t_vec	dir;
}	t_ray;

typedef struct s_material
{
	t_color	rgb;
	double	reflect;
}	t_mat;

typedef struct s_sphere
{
	t_vec			pos;
	t_mat			mat;
	t_ray			r;
	double			radius;
	t_save			save;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec				pos;
	t_vec				ori;
	short int			cap;
	double				radius;
	double				h;
	double				t;
	double				t0;
	double				t1;
	double				dist;
	t_vec				n1;
	t_vec				hit1;
	t_vec				hit2;
	t_vec				hit3;
	t_vec				top;
	t_vec				bot;
	t_vec				i;
	t_vec				o;
	t_mat				mat;
	t_vec				n;
	t_ray				r;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_plane
{
	t_vec			pos;
	t_vec			ori;
	t_mat			mat;
	t_ray			r;
	t_save			save;
	t_vec			n;
	struct s_plane	*next;
}	t_plane;

typedef struct s_camera
{
	t_vec			pos;
	t_vec			dir;
	double			fov;
	struct s_camera	*next;
}	t_cam;

typedef struct s_main_str
{
	double		ali;
	double		rcoef;
	double		reflect;
	double		rx;
	double		ry;
	double		tmpb;
	double		tmpg;
	double		tmpr;
	double		win_scale;
	double		win_ratio;
	int			first_call;
	int			bpp;
	int			endian;
	int			error;
	int			pos;
	int			img_size;
	char		*img_data;
	void		*img_ptr;
	void		*mlx_ptr;
	void		*win_ptr;
	t_cylinder	*cur_cy;
	t_cylinder	*cy;
	t_sphere	*cur_sp;
	t_sphere	*sp;
	t_plane		*cur_pl;
	t_plane		*pl;
	t_color		argb;
	t_light		*cur_li;
	t_light		*li;
	t_cam		*cam;
	t_cam		*cur_cam;
	t_vec		dist;
	t_vec		n;
	t_vec		new_dir;
	t_vec		new_start;
	t_vec		scaled;
	t_ray		r;
	t_mat		*ret;
}	t_mstr;

unsigned int			ft_strlen(char const *str);
void					ft_putstr_fd(char *s, int fd);
int						ft_atoi(const char *str);
double					ft_atof(char *str);
void					check_light(t_mat *ret, t_vec n,
							t_mstr *mstr, double *t);
double					calc_dist_fabs(t_vec v1, t_vec v2);
double					calc_dist(t_vec v1, t_vec v2);
t_vec					calc_v_dir(t_vec	rdir);
t_vec					calc_w_dir(t_vec rdir, t_vec u);
void					cam_lstadd_front(t_cam **alst, t_cam *new);
void					cam_lstadd_back(t_cam **alst, t_cam *new);
t_cam					*cam_lstlast(t_cam *lst);
t_cam					*cam_lstnew(void);
int						cam_lstsize(t_cam *lst);
void					check_vec_error(t_mstr *mstr, t_vec v1,
							t_vec v2, t_vec v3);
void					check_vec_error_inf(t_mstr *mstr,
							t_vec v1, t_vec v2, t_vec v3);
void					check_color_error(t_mstr *mstr, t_color col);
void					color_init(t_color *rgb);
void					compute_all(t_mstr *mstr);
void					compute_camera(t_mstr *mstr, double x, double y);
void					compute_pl(t_mstr *mstr);
unsigned int			create_rgb(int r, int g, int b);
void					create_window(t_mstr *mstr);
void					cy_lstadd_front(t_cylinder **alst, t_cylinder *new);
void					cy_lstadd_back(t_cylinder **alst, t_cylinder *new);
t_cylinder				*cy_lstlast(t_cylinder *lst);
t_cylinder				*cy_lstnew(void);
int						cy_lstsize(t_cylinder *lst);
double					deg2rad(double deg);
int						exit_prog(t_mstr *mstr);
int						find_closest_sp(float discr, double c,
							double b, double *t);
int						handle_key(int key_code, t_mstr *mstr);
int						handle_mouse(int key_code, int x, int y, t_mstr *mstr);
void					li_lstadd_front(t_light **alst, t_light *new);
void					li_lstadd_back(t_light **alst, t_light *new);
t_light					*li_lstlast(t_light *lst);
t_light					*li_lstnew(void);
unsigned int			min(double a, double b);
void					no_leaks(t_mstr *mstr);
t_vec					new_vec3(double x, double y, double z);
int						li_lstsize(t_light *lst);
void					pl_lstadd_front(t_plane **alst, t_plane *new);
void					pl_lstadd_back(t_plane **alst, t_plane *new);
t_plane					*pl_lstlast(t_plane *lst);
t_plane					*pl_lstnew(void);
int						pl_lstsize(t_plane *lst);
void					parsing_id(t_mstr *mstr, char *str);
void					parsing_amb(t_mstr *mstr, char *str);
void					parsing_camera(t_mstr *mstr, char *str);
void					parsing_cylinder(t_mstr *mstr, char *str);
void					parsing_light(t_mstr *mstr, char *str);
void					parsing_sphere(t_mstr *mstr, char *str);
void					parsing_plane(t_mstr *mstr, char *str);
int						rtc_sp(t_mstr *mstr, t_ray *r,
							double *t, int level);
int						rtc_cy(t_mstr *mstr, t_ray *r, double *t);
int						rtc_tr(t_mstr *mstr, t_ray *r, double *t);
int						rtc_sq(t_mstr *mstr, t_ray *r, double *t);
int						rtc_pl(t_mstr *mstr, t_ray *r, double *t);
int						rtc_di(t_mstr *mstr, t_ray *r, double *t);
int						read_file(t_mstr *mstr, int fd);
int						raytracing(t_mstr *mstr);
int						rgb_manage(double r, double g, double b);
void					sp_lstadd_back(t_sphere **alst, t_sphere *new);
void					sp_lstadd_front(t_sphere **alst, t_sphere *new);
t_sphere				*sp_lstlast(t_sphere *lst);
t_sphere				*sp_lstnew(void);
int						sp_lstsize(t_sphere *lst);
t_vec					vec_add(t_vec v1, t_vec v2);
t_vec					vec_cross(t_vec v1, t_vec v2);
t_vec					vec_divide(t_vec v1, t_vec v2);
void					vec_init(t_vec *v1);
void					vec_init_inf(t_vec *v1);
t_vec					vec_add(t_vec v1, t_vec v2);
double					vec_dot(t_vec v1, t_vec v2);
t_vec					vec_normalize(t_vec v1);
t_vec					vec_scale(double c, t_vec v);
t_vec					vec_sub(t_vec v1, t_vec v2);
int						get_next_line(int fd, char **line);
#endif
