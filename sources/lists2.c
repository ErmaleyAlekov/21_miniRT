#include "../includes/mini_rt.h"

void	pl_lstadd_back(t_pl **alst, t_pl *new)
{
	t_pl	*tmp;

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

t_pl	*pl_lstnew(void)
{
	t_pl	*list;

	list = (t_pl *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

t_li	*li_lstnew(void)
{
	t_li	*list;

	list = (t_li *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

void	sp_lstadd_back(t_sp **alst, t_sp *new)
{
	t_sp	*tmp;

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

t_sp	*sp_lstnew(void)
{
	t_sp	*list;

	list = (t_sp *)malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}
