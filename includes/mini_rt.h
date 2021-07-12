#ifndef MINI_RT_H
# define MINI_RT_H
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# define EPSILON 0.0000001f

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

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
	t_vector	pos1;
}	t_save;

typedef struct s_light
{
	t_vector		pos;
	double			intensity;
	t_color			color;
	t_save			save;
	struct s_light	*next;
}	t_light;

typedef struct s_ray
{
	t_vector	start;
	t_vector	dir;
}	t_ray;

typedef struct s_material
{
	t_color	rgb;
	double	reflect;
}	t_mat;

typedef struct s_sphere
{
	t_vector		pos;
	t_mat			mat;
	t_ray			r;
	double			radius;
	t_save			save;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector			pos;
	t_vector			ori;
	short int			cap;
	double				radius;
	double				h;
	double				t;
	double				t0;
	double				t1;
	double				dist;
	t_vector			n1;
	t_vector			hit1;
	t_vector			hit2;
	t_vector			hit3;
	t_vector			top;
	t_vector			bot;
	t_vector			i;
	t_vector			o;
	t_mat				mat;
	t_vector			n;
	t_ray				r;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_plane
{
	t_vector		pos;
	t_vector		ori;
	t_mat			mat;
	t_ray			r;
	t_save			save;
	t_vector		n;
	struct s_plane	*next;
}	t_plane;

typedef struct s_camera
{
	t_vector		pos;
	t_vector		dir;
	double			fov;
	struct s_camera	*next;
}	t_cam;

typedef struct s_mini_rt
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
	t_vector	dist;
	t_vector	n;
	t_vector	new_dir;
	t_vector	new_start;
	t_vector	scaled;
	t_ray		r;
	t_mat		*ret;
}	t_mrt;

unsigned int			ft_strlen(char const *str);
void					ft_putstr_fd(char *s, int fd);
int						ft_atoi(const char *str);
double					ft_atof(char *str);
void					check_light(t_mat *ret, t_vector n,
							t_mrt *mrt, double *t);
double					calc_dist_fabs(t_vector v1, t_vector v2);
double					calc_dist(t_vector v1, t_vector v2);
t_vector				calc_v_dir(t_vector	rdir);
t_vector				calc_w_dir(t_vector rdir, t_vector u);
void					cam_lstadd_front(t_cam **alst, t_cam *new);
void					cam_lstadd_back(t_cam **alst, t_cam *new);
t_cam					*cam_lstlast(t_cam *lst);
t_cam					*cam_lstnew(void);
int						cam_lstsize(t_cam *lst);
void					check_vector_error(t_mrt *mrt, t_vector v1,
							t_vector v2, t_vector v3);
void					check_vector_error_inf(t_mrt *mrt,
							t_vector v1, t_vector v2, t_vector v3);
void					check_color_error(t_mrt *mrt, t_color col);
void					color_init(t_color *rgb);
void					compute_all(t_mrt *mrt);
void					compute_camera(t_mrt *mrt, double x, double y);
void					compute_pl(t_mrt *mrt);
unsigned int			create_rgb(int r, int g, int b);
void					create_window(t_mrt *mrt);
void					cy_lstadd_front(t_cylinder **alst, t_cylinder *new);
void					cy_lstadd_back(t_cylinder **alst, t_cylinder *new);
t_cylinder				*cy_lstlast(t_cylinder *lst);
t_cylinder				*cy_lstnew(void);
int						cy_lstsize(t_cylinder *lst);
double					deg2rad(double deg);
int						exit_prog(t_mrt *mrt);
int						find_closest_sp(float discr, double c,
							double b, double *t);
int						handle_key(int key_code, t_mrt *mrt);
int						handle_mouse(int key_code, int x, int y, t_mrt *mrt);
void					li_lstadd_front(t_light **alst, t_light *new);
void					li_lstadd_back(t_light **alst, t_light *new);
t_light					*li_lstlast(t_light *lst);
t_light					*li_lstnew(void);
unsigned int			min(double a, double b);
void					no_leaks(t_mrt *mrt);
t_vector				new_vec3(double x, double y, double z);
int						li_lstsize(t_light *lst);
void					pl_lstadd_front(t_plane **alst, t_plane *new);
void					pl_lstadd_back(t_plane **alst, t_plane *new);
t_plane					*pl_lstlast(t_plane *lst);
t_plane					*pl_lstnew(void);
int						pl_lstsize(t_plane *lst);
void					parsing_hub(t_mrt *mrt, char *str);
void					parsing_amb(t_mrt *mrt, char *str);
void					parsing_camera(t_mrt *mrt, char *str);
void					parsing_cylinder(t_mrt *mrt, char *str);
void					parsing_light(t_mrt *mrt, char *str);
void					parsing_sphere(t_mrt *mrt, char *str);
void					parsing_plane(t_mrt *mrt, char *str);
int						raytracer_sp(t_mrt *mrt, t_ray *r,
							double *t, int level);
int						raytracer_cy(t_mrt *mrt, t_ray *r, double *t);
int						raytracer_tr(t_mrt *mrt, t_ray *r, double *t);
int						raytracer_sq(t_mrt *mrt, t_ray *r, double *t);
int						raytracer_pl(t_mrt *mrt, t_ray *r, double *t);
int						raytracer_di(t_mrt *mrt, t_ray *r, double *t);
int						reading_file(t_mrt *mrt, int fd);
int						raytracing(t_mrt *mrt);
int						rgb_manage(double r, double g, double b);
void					sp_lstadd_back(t_sphere **alst, t_sphere *new);
void					sp_lstadd_front(t_sphere **alst, t_sphere *new);
t_sphere				*sp_lstlast(t_sphere *lst);
t_sphere				*sp_lstnew(void);
int						sp_lstsize(t_sphere *lst);
t_vector				vector_add(t_vector v1, t_vector v2);
t_vector				vector_cross(t_vector v1, t_vector v2);
t_vector				vector_divide(t_vector v1, t_vector v2);
void					vector_init(t_vector *v1);
void					vector_init_inf(t_vector *v1);
t_vector				vector_add(t_vector v1, t_vector v2);
double					vector_dot(t_vector v1, t_vector v2);
t_vector				vector_normalize(t_vector v1);
t_vector				vector_scale(double c, t_vector v);
t_vector				vector_sub(t_vector v1, t_vector v2);
int						get_next_line(int fd, char **line);
#endif
