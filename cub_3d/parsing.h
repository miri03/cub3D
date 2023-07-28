/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:15:23 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 16:42:31 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAG "\e[1;35m"
# define RESET "\e[0m"

# define TRUE 1
# define FALSE 0

void			error_mess(char *msg);

char			*get_next_line(int fd);
char			**ft_space_split(char const *s, char c, char d);
void			pars_color(char *line, t_mlx *m, int ident);
void			pars_rgb(char *rgb);
int				check_rgb(char *str);
void			check_ident(char **line, t_mlx *m, int *sky, int *floor);
int				textures(int fd, t_mlx *m);
int				check_line(char *line, t_mlx *m, int *sky, int *floor);
int				start_map(char *line);
void			map(char *file_path, int start, t_mlx *m);
int				n_line(char *line);
int				empty_line(char **line);
void			free_tab(char **tab);
void			pars_map(char **map, t_mlx *m);
void			map_starting(int fd, int start);
int				tab_len(char **tab);
int				max_len(char *file_path, int start);
void			height_len(int fd, t_mlx *m);
int				empty(char *line);
void			check_textures(char **line, t_mlx *m);
void			free_tab(char **tab);
int				empty_line(char **line);
void			fill_path(int direction, char *path, t_mlx *m);
int				start_pos(char c);
char			put_line_uti(char c);
void			init_pars(t_mlx *m);
int				open_map(char *map);
int				n_line(char *line);
void			map_starting(int fd, int start);

// ----- libft ----- //
char			**ft_split(char const *s, char c);
int				ft_strcmp(char *s1, char *s2);
int				ft_isdigit(int c);
unsigned long	ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strdup(const char *s1);

#endif