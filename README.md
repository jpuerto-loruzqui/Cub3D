<p align="end">
  <strong>🌐 Change language:</strong><br>
  <a href="/README.es.md">
   <img src="https://github.com/Nachopuerto95/multilang/blob/main/ES.png" alt="Español" width="50">
 </a>&nbsp;&nbsp;&nbsp;
 <a href="/README.md">
   <img src="https://github.com/Nachopuerto95/multilang/blob/main/EN.png" alt="English" width="50">
 </a>
</p>


# Cub3D (42cursus)

<img src="https://github.com/Nachopuerto95/multilang/blob/main/42-Madrid%20-%20Edited.jpg">

---

> [!WARNING]
> **This guide is an educational aid for understanding the 42 Cub3D project. It is NOT intended as a step-by-step guide or the only way to tackle the project.**
>  
> If you want to go straight to the final message, [click here](#acknowledgments-and-final-note).

---

## 📑 Index

- [About the Project](#about-the-project)
- [Description](#description)
- [Guide for Cub3d 42](#guide-for-cub3d-42)
  - [Main Loop and Hooks](#main)
  - [Drawing the Map](#drawing-the-map)
  - [Player Movement](#player-movement)
  - [Ray Casting](#ray-casting)
  - [Calculating Distance (Raycasting and DDA)](#calculating-distance-raycasting-and-dda)
  - [Wall Height and Texturing](#adding-textures)
  - [Shading and Darkening](#shading)
- [Acknowledgments and Final Note](#acknowledgments-and-final-note)

---

## 📜 About the Project

```html
🕹️ Cub3D is a project where you'll learn the basics of 3D graphics by creating a
simple graphics engine based on raycasting, inspired by classics like Wolfenstein 3D.
```

> **42 School Norms:**  
> * Each function cannot have more than 25 lines of code.
> * All variables must be declared and aligned at the top of each function.
> * The project must be created using only the allowed functions.

---

### 📌 Description

Cub3D consists of developing a small 3D graphics engine using the raycasting technique. The goal is to render a maze-like environment in first-person, allowing the user to explore it.

This repository contains a full implementation of the Cub3D project, developed in C, complying with the restrictions and rules established by 42 School.

---

# 🚀 Guide for Cub3d 42

To explain this project and reinforce my understanding, I decided to create a sort of guide that other 42 students can use to support themselves in the initial phases of the project, as well as in using the Minilibx library, which you’ve likely already used in other cursus projects.

We’ll start by explaining how the main hooks of the library work for the game, player movement, and the raycasting algorithm (in a simplified version).

---

## Main

```c
int main(void)
{
    t_game game;
    init_game(&game);

    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);
    return 0;
}
```

In the `game` structure, we’ll add the necessary variables for mlx (`mlx`, `win`...), and more as we go. After declaring our structure and defining its initial variables, we start with the hooks.

---

### Hooks

**Keyboard hooks:**
```c
mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
```
The first argument is the window, the second and third refer to the key press and key release events (leave them as is), then the name of the function we created (in my case, `key_press()` and `key_release()`, but you can name them however you like). Finally, a pointer to the structure where we’ll make changes.

For example, if I want the player’s Y position to increase while W is pressed, I need the player structure to change its `posY`.

---

**Loop hook:**

Almost all games need a game loop to function properly. This loop is a cycle that runs continuously while the game is running. Its function is:

- Process user input (keyboard, mouse, etc.)
- Update the position of the player and environment elements
- Detect collisions
- Redraw the screen with the new information

Just like the other hooks, we’ll give it a function that will be repeated continuously.

We’ll divide this function into three main actions: clear, recalculate, and draw.

---

For the canvas, you should have something like this:

```c
game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
```

To "clear" the screen, just loop from `x = 0` and `y = 0` up to `x = WIDTH` and `y = HEIGHT`, filling each pixel with the background color.

---

First, we’ll need the following variables in our game structure:

- `char *data`;  
  A pointer to the start of the byte array representing the full image in memory. Each pixel you draw modifies this array.
- `int bpp`;  
  "Bits per pixel" — number of bits per pixel (usually 32 in MiniLibX, i.e., 4 bytes per pixel).
- `int size_line`;  
  Number of bytes that a complete line of the image occupies. This may be slightly more than WIDTH * (bpp / 8) due to memory alignment.
- `int endian;`  
  Indicates the byte order in memory (little/big endian). Usually irrelevant if you only use basic colors and MiniLibX on Linux.

We’ll initialize the `addr` in our structure (I did this in the `init_game` function that prepares all variables before the hooks), followed by the first image display:

```c
game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
```

What does `mlx_put_image_to_window` do?

This is important: on each frame, you calculate the color of every pixel on the screen and store it in the `data` array (your image in RAM). Then `mlx_put_image_to_window` puts it in the window.

- Multiply `y * size_line` → Skips all previous rows.
- Multiply `x * (bpp / 8)` → Moves within the row to the x column.
- Add both → You get the exact position in `data` for that pixel.

Let’s write a function that, given the x and y position of the pixel and its color, will put that pixel in the right spot in the array:

```c
void	ft_put_pixel_t(int x, int y, unsigned int color, t_game *game)
{
    char	*dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) // Checks if the pixel is within the screen
        return;
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *) dst = color;
}
```

---

## Drawing the Map

To make the raycasting explanation more accessible to those who have never heard about it, let’s start by showing a top-down map view.

I created a simple function to draw a square, given the position, size, and color:

```c
void draw_square(int x, int y, int size, int color, t_game *game)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}
```

Now create a function that reads your map matrix and for every `1` draws a square of one color, and for every `0`, a square of another. (For the walls, I use another function...)

Call this "draw_map" function on each iteration of the main loop, along with another one that draws the player.
The player’s position will, for now, be at the center of the screen, so in the player structure, we’ll put its posX and posY at `width / 2` and `height / 2`.

The (very simplified) loop should look like this:

```c
int draw_loop(t_game *game)
{
    t_player *player = &game->player;

    clear_image(game); // Clear

    draw_square(player->x, player->y, 10, 0x00FF00, game); // draw player
    draw_map(game); // draw map
    
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}
```

Start your game, and after fixing issues I haven’t explained or that may have come up (don’t worry, it’s your first attempt), you should be able to see...

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/Captura%20desde%202025-09-02%2008-50-09.png?raw=true" alt="Cub3D Screenshot" width="400"/>
</p>

---

## Player Movement

To move the player square, let’s make a couple of simple functions we mentioned earlier: `key_press()` and `key_release()`, which we’ve passed to the keyboard hooks.
These functions just set a series of booleans in our player structure, each referencing a key, so our structure will store...

When you press a key, the hook is triggered, generating a "keycode" for the pressed key, which is then passed to the function you specify.

```c
mlx_hook(game.win, 2, 1L<<0, key_press, &game.player); // here’s the hook
```

```c
int key_press(int keycode, t_player *player)
{
    if(keycode == W)
        player->key_up = true;
    if(keycode == S)
        player->key_down = true;
    if(keycode == A)
        player->key_left = true;
    if(keycode == D)
        player->key_right = true;
    if(keycode == LEFT)
        player->left_rotate = true;
    if(keycode == RIGHT)
        player->right_rotate = true;
    return 0;
}
```

The constants `W` `A` `S` `D`... are saved in my .h file so I don’t put the actual keycodes here, which aren’t very intuitive. In my case, the keycodes are:

```c
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
```

The `key_release()` function is the same, but sets the variables to `false`.

Now we can add a `move_player()` function to our loop, which recalculates the player’s position every frame.
Moving up, down, and sideways is simple: create a constant called `PLAYER_SPEED` and in the move function say that while `player->key_up == true`, you advance `PLAYER_SPEED` in the correct direction...

Do this for all the keys you have as booleans in your player structure. By including `move_player()` before the drawing functions, you’ll have a basic moving structure.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/ezgif-88233df297ca3c.gif" alt="Cub3D Screenshot" width="400"/>
</p>

For playability, you control the player’s position with `WASD` and the direction (where the player "looks") with the left/right arrow keys (we change their viewing angle).
For this, we need sine and cosine, which I’ll try to explain as simply as possible.

The player will have a new variable: `angle`, which broadly defines the direction they’re facing.

It’s common to define the player’s direction using an angle in radians.
Normally, the positive X axis is the reference (facing right), and the angle increases counterclockwise:

- Right: 0 radians (or 2π, same thing)
- Up: π/2 radians
- Left: π radians
- Down: 3π/2 radians (or -π/2)

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/pi-angles.png" alt="Cub3D Screenshot" width="400"/>
</p>

Basically, we’ll initialize `angle` in one of these directions, depending on where we want the player to look when the game starts.

```html
Save a constant PI in your .h file with about 12 decimals, we’ll use it a lot.
```

We’ll also need an `ANGLE_SPEED` constant, the speed at which the player rotates. I set it to 0.01. Add this value to angle every time the player rotates.

```c
if (player->arrow_left)
    player->angle -= angle_speed;
if (player->arrow_right)
    player->angle += angle_speed;
if (player->angle > 2 * PI)
    player->angle = 0;
if (player->angle < 0)
    player->angle = 2 * PI;
```

The angle directly affects player movement with WASD, since now pressing W makes the player move in the direction of the angle.

---

### What are sine and cosine in this context?

Sine (sin) and cosine (cos) are math functions that tell you “how much you move in X” (horizontal) and “how much you move in Y” (vertical) when moving in the direction you’re pointing.
Imagine a circle. The angle (`player->angle`) is where the arrow/player is pointing.
Cosine is the horizontal movement (X), sine is the vertical movement (Y).

Why do we need them here?
They let you move the player in the direction they’re facing, not just up/down/left/right fixed on the screen.

For example: If you look up-right, you’ll move diagonally just by pressing `W`.

To move forward/back, add or subtract `cos(angle)` for x and `sin(angle)` for y. For sideways, swap and use `sin(angle)` for x and `cos(angle)` for y:

```c
if (player->key_up)
{
    player->x += cos_angle * PLAYER_SPEED;
    player->y += sin_angle * PLAYER_SPEED;
}
if (player->key_down)
{
    player->x -= cos_angle * PLAYER_SPEED;
    player->y -= sin_angle * PLAYER_SPEED;
}
if (player->key_left)
{
    player->x += sin_angle * PLAYER_SPEED;
    player->y -= cos_angle * PLAYER_SPEED;
}
if (player->key_right)
{
    player->x -= sin_angle * PLAYER_SPEED;
    player->y += cos_angle * PLAYER_SPEED;
}
```

Simple, right?  
Now let’s cast our first ray in the direction of the angle to make everything so far more obvious.

---

## Ray Casting

```c
void draw_line(t_player *player, t_game *game, float angle, int i)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    float ray_x = player->x;
    float ray_y = player->y;

    while(!touch(ray_x, ray_y, game))
    {
        put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
}
```
Drawing the line is like moving: we paint pixels at ray_x, ray_y, incrementing in the direction given by sine and cosine of the angle, but instead of depending on a key, we do it in the loop.

```c
bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
    if(game->map[y][x] == '1')
        return true;
    return false;
}
```

Notice we divide `px / BLOCK`, since px refers to the screen (e.g., 576x448), and to get the map matrix position, we divide by the cell size.

Once implemented, your program should look like this, with your first ray cast. From here, everything will make more sense.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/ezgif-76bd7f53bd990d.gif" alt="Cub3D Screenshot" width="400"/>
</p>

The next step is to cast a few more rays for a more visual explanation.

Before, we cast a ray in the angle direction. To draw an arc, let’s introduce two more variables and, for testing, cast 10 rays:

```c
float fraction = PI / 3 / 10; // Defines the distance between each ray
float start_x = player->angle - PI / 6; // Defines the field of view angle.
```

Let’s explain the field of view a bit more:

A field of view of π/3 radians equals 60 degrees.

To convert radians to degrees, multiply by 180 and divide by π:

```html
(π / 3) × (180 / π) = 60°
```
We want a 60º FOV, i.e., π / 3, so our arc will go from angle - (π / 6) up to angle + (π / 6), so the total is π / 3, with the player’s angle in the center.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/FOV-img.png" alt="Cub3D Screenshot" width="400"/>
</p>

In our test with 10 rays, we get the `fraction` (separation between rays) from the total FOV (`PI / 3`) divided by the number of rays (`10`) and `start_x` as the starting angle (`PI / 6`).

If, in the loop, instead of drawing a ray from the player’s angle, we make a loop that draws 10 rays, from `start_x`, adding `fraction` each time, we’ll see the arc:

```c
while(i < 10)
{
    draw_line(player, game, start_x, i);
    start_x += fraction;
    i++;
}
```
And the result:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/fov-10-rays.gif" alt="Cub3D Screenshot" width="400"/>
</p>

Now imagine you take each of those rays, calculate the distance to the wall, and from that distance you calculate the height of the "vertical line of pixels" for that ray:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/20rays.gif" alt="Cub3D Screenshot" width="400"/>
</p>

And if you cast a ray for each pixel across your game’s width (576px for me), you can draw the vertical line for each, getting something like this:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/fullwidthrays.gif" alt="Cub3D Screenshot" width="400"/>
</p>

---

## Calculating Distance (Raycasting and DDA)

As you can see in the gif above, there’s a bug when checking pixel-by-pixel collisions called the "corner bug," which doesn’t recognize collisions between two adjacent diagonal cells. For this, we use the DDA algorithm for raycasting.

This algorithm uses trigonometry to calculate which wall our ray hits.

Let’s analyze the `draw_line` function step by step:

First, initialize the data with `ft_init_line_data`:

- With `ft_init_line`, we calculate the ray’s direction with `sin` and `cos`, calculate the player’s relative position in the map, and calculate `delta_dist`.
- `ft_get_delta_dist`: `delta_dist_x` and `delta_dist_y` are the distances the ray travels between a line of one axis and another of the same axis; this is constant:

```c
deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY)
```

This formula comes from Pythagoras’ theorem, but can be simplified as shown.

Once we have delta_dist, we need to know which direction the "steps" go and what the initial `side_dist` is:

```c
void	ft_calculate_steps(t_line *l, t_player *player)
{
    if (l->ray_dir_x < 0)
    {
        l->step_x = -1;
        l->side_dist_x = (player->x / BLOCK - l->map_x) * l->delta_dist_x;
    }
    else
    {
        l->step_x = 1;
        l->side_dist_x = (l->map_x + 1.0 - player->x / BLOCK) * l->delta_dist_x;
    }
    if (l->ray_dir_y < 0)
    {
        l->step_y = -1;
        l->side_dist_y = (player->y / BLOCK - l->map_y) * l->delta_dist_y;
    }
    else
    {
        l->step_y = 1;
        l->side_dist_y = (l->map_y + 1.0 - player->y / BLOCK) * l->delta_dist_y;
    }
}
```

This way, we’ll know if the steps in each axis go +1 or -1, and what the distance is from the player (who usually starts in the middle of a cell) to the first axis.

---

Once we have all this, we can apply DDA:

```c
void	ft_dda(t_game *game, t_line *l)
{
    int	hit = 0;
    while (hit == 0)
    {
        if (l->side_dist_x < l->side_dist_y)
        {
            l->side_dist_x += l->delta_dist_x;
            l->map_x += l->step_x;
            l->side = 0;
        }
        else
        {
            l->side_dist_y += l->delta_dist_y;
            l->map_y += l->step_y;
            l->side = 1;
        }
        if (game->map[l->map_y][l->map_x] == '1'
            || game->map[l->map_y][l->map_x] == 'C'
            || game->map[l->map_y][l->map_x] == 'D')
            hit = 1;
    }
}
```

At each step, the ray advances to the next cell line (in X or Y) depending on which is closer by adding delta_dist. When it hits a cell that is a wall ('1', 'C', 'D'), the loop ends. We also store if side is 0 (hit X axis) or 1 (hit Y axis).

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/dda_sides.png" height="250"/>
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/dda_gif.gif" height="250"/>
</p>

---

Once we’ve done the algorithm, we can calculate the distance with `ft_get_dist()`:

```c
float ft_get_dist(t_player *player, t_line l, float ray_angle)
{
    float perp_wall_dist;
    float corrected_dist;
    
    if (l.side == 0)
        perp_wall_dist = (l.map_x - player->x / BLOCK + (1 - l.step_x) / 2) / l.ray_dir_x;
    else
        perp_wall_dist = (l.map_y - player->y / BLOCK + (1 - l.step_y) / 2) / l.ray_dir_y;
    corrected_dist = perp_wall_dist * cos(ray_angle - player->angle);

    return corrected_dist * BLOCK;
}
```

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/raycastperpwalldist2%20(1).png" height="250"/>
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/1RAY_CORRECTION.png" height="250"/>
</p>

If you look at the image on the right, you’ll see that when looking straight at a wall (which should look flat), the distance to the corners is much greater than in the center, which is why we do this correction.

To calculate this distance, we multiply the perpendicular distance by the cosine of `ray_angle - player->angle`.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/0RAY_CORRECTION.png" alt="Cub3D Screenshot" width="400"/>
</p>

Once we have the distance, in `ft_init_line_data()` we complete the data as follows:

```c
d->height = (BLOCK * HEIGHT * SCALE_BLOCK) / d->l.dist;
d->start_y = (HEIGHT - d->height) / 2;
d->end = d->start_y + d->height;
if (d->start_y < 0)
    d->start_y = 0;
if (d->end > HEIGHT)
    d->end = HEIGHT;
```

`SCALE_BLOCK` is a constant used to vary the wall size.
start and end are where we start to draw the vertical line, centering it horizontally.

---

## Adding textures

Let’s look at our `draw_line()` function. Several things happen here.

```c
void	ft_draw_line(t_player *player, t_game *game, float start_x, int i)
{
    t_draw_data	d;

    ft_init_line_data(&d, player, game, start_x);
    ft_calc_wall_position(&d, player);
    ft_calc_texture_data(&d, game);
    ft_draw_wall_column(&d, game, i);
}
```

As said, this function draws a vertical line; there will be as many lines as the width of our canvas in pixels, and this line uses the variables we filled in...

From y = 0 to y = start_y we draw the ceiling color.

From start_y to end we draw the corresponding texture line; as we used BLOCK = 64 and our texture is also 64 px, we need to know the exact point where our ray hit.

Finally, the floor color goes from `end` to `y = HEIGHT`.

```c
void	ft_calc_wall_position(t_draw_data *d, t_player *player)
{
    if (d->l.side == 0)
        d->wall_x = player->y + d->l.dist * d->l.ray_dir_y;
    else
        d->wall_x = player->x + d->l.dist * d->l.ray_dir_x;
    d->wall_x = d->wall_x - floor(d->wall_x / BLOCK) * BLOCK;
    d->tex_x_normalized = d->wall_x / BLOCK;
    d->tex_index = ft_get_wall_c(d->l.side, d->l.step_x, d->l.step_y);
}
```

If the ray hit a vertical wall (`side == 0`), we calculate the exact collision point using the player’s Y position and the ray’s Y component.  
If it hit a horizontal wall (`side == 1`), we use the X position and the ray’s X component.
`d->l.dist` is the distance from the player to the wall.
`d->l.ray_dir_x` and `d->l.ray_dir_y` indicate the ray’s direction.

Numerical example:  
Suppose the player is at `player->y = 100`, the ray goes up (`d->l.ray_dir_y = 1.0`), the wall distance (`d->l.dist`) is 32:

```c
d->wall_x = 100 + 32 * 1.0;  // result: 132
```

```c
d->wall_x = d->wall_x - floor(d->wall_x / BLOCK) * BLOCK;
```
This calculates the exact impact position inside the wall block.  
If your block is 64 pixels (`BLOCK=64`) and the hit was at x=130:

- `floor(130 / 64) = 2`
- `2 * 64 = 128`
- `130 - 128 = 2`

So wall_x gives the offset within the block, from 0 to 63.

To handle textures that don’t match BLOCK size, we normalize the point, converting it into a 0-1 value so if it hits `x=32`, `tex_x_normalized` is 0.5.

Next, we determine which of the 4 faces to render with `ft_get_wall_c()`, which returns the index for the texture in our texture array.

The next function is:

```c
void	ft_calc_texture_data(t_draw_data *d, t_game *game)
{
    d->tex_x = (int)(d->tex_x_normalized * game->textures[d->tex_index].width);
    d->step = 1.0 * game->textures[d->tex_index].height / d->height;
    d->tex_pos = (d->start_y - HEIGHT / 2 + d->height / 2) * d->step;
    d->y = d->start_y;
}
```
Step by step, we convert the normalized value to a position in the full texture width:

```c
d->tex_x = (int)(d->tex_x_normalized * game->textures[d->tex_index].width);
```
The `step` indicates how many texture pixels to skip each time you draw a wall pixel on screen.  
If the wall is taller than the texture, `step < 1` (texture stretches). If it’s shorter, `step > 1` (texture compresses).

```c
d->step = 1.0 * game->textures[d->tex_index].height / d->height;
```

Calculate the initial position in the texture:

```c
d->tex_pos = (d->start_y - HEIGHT / 2 + d->height / 2) * d->step;
```
- `d->start_y` is the first vertical pixel where the wall starts on screen.
- `HEIGHT / 2` is the vertical center of the window.
- `d->height / 2` is half the wall’s height.

This formula sets the initial position (in the texture) so the mapping is centered with respect to the drawn wall.
Multiplying by `d->step` converts the screen position to the corresponding texture position.

Finally, draw the texture:

```c
void	ft_draw_wall_column(t_draw_data *d, t_game *game, int i)
{
    while (d->y < d->end)
    {
        d->tex_y = (int)d->tex_pos % game->textures[d->tex_index].height;
        if (d->tex_y < 0)
            d->tex_y += game->textures[d->tex_index].height;
        d->tex_pos += d->step;
        d->pixel_addr = game->textures[d->tex_index].addr
            + (d->tex_y * game->textures[d->tex_index].size_line
                + d->tex_x * (game->textures[d->tex_index].bpp / 8));
        d->color = *(unsigned int *)d->pixel_addr;
        if (d->l.side == 0 && !ft_is_light(d->color))
            d->color = (d->color >> 1) & 8355711;
        d->color = ft_get_darkness(d->color, d->height);
        ft_put_pixel_t(i, d->y, d->color, game);
        d->y++;
    }
}
```

A key point here is how the texture is drawn and how it’s compressed or stretched depending on the wall’s distance.
For the x axis, for example, if you’re right in front of a wall that fills 800px of screen width, each ray hit a different pixel on the wall, and you calculate a different tex_x for each screen column.
For the y axis, as explained, you use the step variable: if it’s < 1, you “repeat” pixels; if it’s > 1, you skip some.

---

## Shading

Darken the color if it’s a vertical wall:

```c
if (d->l.side == 0 && !ft_is_light(d->color))
    d->color = (d->color >> 1) & 8355711;
```

In my case, to create an effect, I chose to make west walls have a "light" and east walls use a slightly tinted texture to fake light reflection.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/shading01.png" alt="Cub3D Screenshot" width="400"/>
</p>

You can see that by darkening vertical walls and using this effect on horizontals, we get a greater sense of depth. To enhance this even more, we can add a distance factor:

```c
unsigned int	ft_get_darkness(unsigned int color, float height)
{
    float			darkness;
    unsigned int	r;
    unsigned int	g;
    unsigned int	b;

    darkness = ((float)height * 0.9) / ((float)HEIGHT * 0.7f); // adjust max/min values
    if (darkness > 1.0f)
        darkness = 1.0f;
    if (darkness < 0.01f)
        darkness = 0.00f;
    if (ft_is_light(color))
        return (color);
    r = ((color >> 16) & 0xFF) * darkness;
    g = ((color >> 8) & 0xFF) * darkness;
    b = (color & 0xFF) * darkness;
    return ((r << 16) | (g << 8) | b);
}
```
I picked color exceptions so they don’t darken, simulating a light:

```c
bool	ft_is_light(unsigned int color)
{
    if (color == LIGHT_COLOR_1 || color == LIGHT_COLOR_2
        || color == 0x00FF00)
        return (true);
    return (false);
}
```

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/shading02.png" alt="Cub3D Screenshot" width="400"/>
</p>

If you now add textures to the floor and ceiling, you get this final result:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/finalgifbonus.gif" alt="Cub3D Screenshot"/>
</p>

---

## <a name="acknowledgments-and-final-note"></a>🙏 Acknowledgments and Final Note

> **Thank you for reading.**  
> This is not intended as a step-by-step guide, but rather support for understanding some mathematical formulas and the main problems I’ve encountered while working on the Cub3D project.
>
> If you found the content useful, please leave a star ⭐️ or a follow.

---
