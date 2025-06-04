#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# include <stdio.h>
//#include <X11/keysym.h>

typedef struct s_game
{
    char    **map;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     moves;
    int     tile_size;
    void    *mlx;
    void    *win;
    void    *img_player;
    void    *img_wall;
    void    *img_floor;
    void    *img_ball;
    void    *img_exit;
}   t_game;

// Funções de parsing e validação do mapa

int parse_map(const char *filename, t_game *game);
int alloc_and_read_map(const char *filename, t_game *game);
int find_player_position(t_game *game);
void    free_map(char **map, int height);
void    error_and_exit(const char *msg);
int     ft_strlen(const char *str);
// Funções auxiliares
size_t      ft_len_till_eol(const char *s, char c);
char    *ft_strdup(const char *s);
unsigned int ft_strlcat(char *dst, const char *src, unsigned int size);
char    *get_next_line(int fd);
// Funções de leitura do mapa
int count_lines(const char *filename);
char *ft_strjoin(char *s1, char *s2);
void ft_strlcpy(char *dst, char *src, size_t size);
// Funções de validação do mapa
int is_rectangular(t_game *game);
int has_only_valid_characters(t_game *game);
int is_surrounded_by_walls(t_game *game);
int has_required_elements(t_game *game);
int validate_map(t_game *game);
void count_map_elements(t_game *game, int *exit, int *collectible, int *player);
// Funções de renderização
void init_window(t_game *game);
void load_images(t_game *game);
void render_map(t_game *game);

int	handle_keypress(int keycode, t_game *game);
int	handle_destroy(t_game *game);
int	exit_game(t_game *game);
// Funções de movimentação
int	can_move_to(t_game *game, int x, int y);
void	move_player(t_game *game, int dx, int dy);

// Funções de utilidade geral



#endif
