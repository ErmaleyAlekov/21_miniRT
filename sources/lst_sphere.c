#include "../includes/mini_rt.h"

void	sp_lstadd_front(t_sphere **alst, t_sphere *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
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

t_sphere	*sp_lstlast(t_sphere *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

int	sp_lstsize(t_sphere *lst)
{
	int	n;

	if (!lst)
		return (0);
	n = 1;
	while (lst->next)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
