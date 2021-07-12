#include "../includes/mini_rt.h"

void	pl_lstadd_front(t_plane **alst, t_plane *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

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

t_plane	*pl_lstlast(t_plane *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

int	pl_lstsize(t_plane *lst)
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
