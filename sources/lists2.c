#include "../includes/mini_rt.h"

void	pl_lstadd_back(t_plane **alst, t_plane *new)
{
	t_plane	*tmp;

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

t_plane	*pl_lstnew(void)
{
	t_plane	*list;

	list = (t_plane *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

t_light	*li_lstnew(void)
{
	t_light	*list;

	list = (t_light *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

void	sp_lstadd_back(t_sphere **alst, t_sphere *new)
{
	t_sphere	*tmp;

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

t_sphere	*sp_lstnew(void)
{
	t_sphere	*list;

	list = (t_sphere *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}
