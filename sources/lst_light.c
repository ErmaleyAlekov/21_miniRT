#include "../includes/mini_rt.h"

void	li_lstadd_front(t_light **alst, t_light *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
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

t_light	*li_lstlast(t_light *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

int	li_lstsize(t_light *lst)
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
