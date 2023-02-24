#include "Libft/libft.h"


int get_val_index(int val, t_list *lst)
{
	int	i;
	i = 0;
	while (lst)
	{
		if (*((int *) lst->content) == *((int *) val))
			return (i);
		lst = lst->next;
		i++;
	}
	return (-1);
}

/*
	index = get_val_index(VAL);
	if (index < (TOTAL_LST_SIZE - index))
	{
		while (*lst->content != VAL)
			rb(LST);
	}
	else
	{
		while (*lst->content != VAL)
			rrb(LST);
	}
*/