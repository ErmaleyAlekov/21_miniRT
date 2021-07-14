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

void	cy_lstadd_back(t_cyl **alst, t_cyl *new)
{
	t_cyl	*tmp;

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

t_cyl	*cy_lstnew(void)
{
	t_cyl	*list;

	list = (t_cyl *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

void	li_lstadd_back(t_li **alst, t_li *new)
{
	t_li	*tmp;

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
