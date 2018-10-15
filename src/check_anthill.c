/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:01:22 by awajsbro          #+#    #+#             */
/*   Updated: 2018/10/15 13:59:40 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	delete_line(char **s)
{
	if (**s == '\n')
		(*s)--;
	while (**s != '\n')
		(*s)--;
	(*s)++;
	while (**s != 0)
	{
		**s = 0;
		(*s)++;
	}
}

char		cmd_cmt(char **s, t_li *li)
{
	char	m;

	m = 0;
	while (**s == '#')
	{
		if (ft_strnequ(*s, "##end\n", 6) == 1)
			m = m == -1 || m == 0 ? -1 : -42;
		else if (ft_strnequ(*s, "##start\n", 8) == 1)
			m = m == 1 || m == 0 ? 1 : -42;
		*s += ft_strclen(*s, '\n');
		if (**s == '\n')
			*s += 1;
		if ((m == -1 && li->end) || (m == 1 && li->beg) || m == -42)
			return (0);
	}
	if (m == 1)
		li->beg = *s;
	else if (m == -1)
		li->end = *s;
	return (1);
}

char		init_anthill(char *s, t_li *li)
{
	char	tmp[21];
	char	*tmp2;

	cmd_cmt(&s, li);
	li->lem = ft_atoi(s);
	if (ft_istrcmp("2147483648", ft_strncpy(tmp, s, ft_strclen(s, '\n'))) == -1
		|| li->lem < 1)
		return (0);
	while (*s != '\n' && *s != 0)
		s++;
	tmp2 = s + 1;
	if (check_room(&s, li) == 0 || li->end == NULL || li->beg == NULL)
		return (0);
	if (*s == '-')
		while (s[-1] != '\n' && *s != 0)
			s--;
	if (!(save_room(tmp2, s--, li)))
		return (0);
	tmp2 = s + 1;
	if (check_pipe(&s, li) == 0)
		delete_line(&s);
	if (!(save_pipe(tmp2, li, 0, tmp2)))
		return (0);
	return (1);
}
