void    init_game(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 
        game->map_width * TILE_SIZE, 
        game->map_height * TILE_SIZE, 
        "Football So_Long");
    load_textures(game);
}