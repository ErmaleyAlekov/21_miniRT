#include "../includes/mini_rt.h"

void	cam_lstadd_back(t_cam **alst, t_cam *new)
{
	t_cam	*tmp;

	if (!alst || !new)
		return ;
	new->next = 0;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cam	*cam_lstnew(void)
{
	t_cam	*list;

	list = (t_cam *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

void	cy_lstadd_back(t_cylinder **alst, t_cylinder *new)
{
	t_cylinder	*tmp;

	if (!alst || !new)
		return ;
	new->next = 0;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cylinder	*cy_lstnew(void)
{
	t_cylinder	*list;

	list = (t_cylinder *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

void	li_lstadd_back(t_light **alst, t_light *new)
{
	t_light	*tmp;

	if (!alst || !new)
		return ;
	new->next = 0;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
