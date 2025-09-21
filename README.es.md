<p align="end">
  <strong>🌐 Cambiar idioma:</strong><br>
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
> **Esta guía es un apoyo didáctico para comprender el proyecto Cub3D de 42. NO pretende ser una guía paso a paso ni la única forma de abordar el proyecto.**
>  
> Si quieres ir directo al mensaje final, [haz clic aquí](#agradecimientos-y-aviso-final).

---

## 📑 Índice

- [Acerca del Proyecto](#acerca-del-proyecto)
- [Descripción](#descripción)
- [Guía para Cub3d 42](#guía-para-cub3d-42)
  - [Main Loop y Hooks](#main)
  - [Pintando el mapa](#pintando-mapa)
  - [Movimiento del player](#movimiento-del-player)
  - [Casteo de rayos](#casteo-de-rayos)
  - [Calcular distancia (Raycasting y DDA)](#calcular-distancia-raycasting-y-dda)
  - [Altura y texturizado de paredes](#añadir-texturas)
  - [Shading y oscurecimiento](#shading)
- [Agradecimientos y aviso final](#agradecimientos-y-aviso-final)

---

## 📜 Acerca del Proyecto

```html
🕹️ Cub3D es un proyecto donde aprenderás fundamentos de gráficos 3D mediante la creación de un
motor gráfico simple basado en raycasting, inspirado en clásicos como Wolfenstein 3D.
```

> **Norma de la Escuela 42:**  
> * Cada función no puede tener más de 25 líneas de código.
> * Todas las variables deben ser declaradas y alineadas en la parte superior de cada función.
> * El proyecto debe ser creado solo con las funciones permitidas.

---

### 📌 Descripción

Cub3D consiste en desarrollar un pequeño motor gráfico 3D utilizando la técnica de raycasting. El objetivo es renderizar un entorno laberíntico en primera persona, permitiendo al usuario explorarlo.

Este repositorio contiene una implementación completa del proyecto Cub3D, desarrollada en lenguaje C, cumpliendo con las restricciones y normas establecidas por la escuela 42.

---

# 🚀 Guía para Cub3d 42

Para explicar este proyecto y afianzar mis conocimientos sobre el mismo, he decidido hacer una especie de guía que otros alumnos de 42 puedan utilizar para apoyarse en las fases iniciales del proyecto y en el uso de la librería Minilibx, que muy posiblemente hayamos tenido que utilizar en otros proyectos llegados a este punto del cursus.

Comenzaremos por explicar cómo funcionan los principales hooks de la librería necesarios para el juego, el movimiento del jugador y el algoritmo de raycasting (una versión simplificada).

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

En la estructura `game`, vamos a añadir las variables necesarias para mlx (`mlx`, `win`...), añadiremos más cosas en el futuro, pero vamos por orden. Tras declarar nuestra estructura y definir sus variables iniciales, comenzamos con los hooks.

---

### Hooks

**Hooks de teclado:**
```c
mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
```
Como primer argumento le pasamos la ventana, los argumentos segundo y tercero hacen referencia a los eventos key press y key release (déjalos así), después el nombre de la función que hemos creado (en mi caso, `key_press()` y `key_release()` pero podrían llamarse como quieras). Por último, un puntero a la estructura donde haremos los cambios.

Por ejemplo, si yo quiero que mientras W esté pulsado la posición Y del player incremente, necesito la estructura player para cambiar su `posY`.

---

**Hook para el loop:**

Prácticamente todos los juegos necesitan un game loop (bucle de juego) para funcionar correctamente. Este loop es un ciclo que se ejecuta de forma continua mientras el juego está en marcha. Su función es:

- Procesar la entrada del usuario (teclado, ratón…)
- Actualizar la posición del jugador y los elementos del entorno
- Detectar colisiones
- Redibujar la pantalla con la nueva información

De la misma manera que los demás hooks, vamos a pasarle una función, que será la que se repita continuamente.

Vamos a dividir esta función en las 3 acciones principales que va a llevar a cabo: limpiar, recalcular y pintar.

---

Para la creación del canvas ya deberíamos tener algo parecido a esto:

```c
game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
```

De modo que para "limpiar" la pantalla solo debemos hacer un bucle que comience desde `x = 0` e `y = 0` hasta `x = WIDTH` e `y = HEIGHT` rellenando cada pixel con el color de fondo.

---

Primero de todo vamos a necesitar las siguientes variables en nuestra estructura game:

- `char *data`;  
  Es un puntero al inicio del "array" de bytes que representa la imagen completa en memoria. Cada píxel que dibujes modifica este array.
- `int bpp`;  
  "Bits per pixel" — número de bits que ocupa cada píxel (habitualmente 32 en MiniLibX, es decir, 4 bytes por píxel).
- `int size_line`;  
  Número de bytes que ocupa una línea completa de la imagen. Esto puede ser un poco mayor que WIDTH * (bpp / 8) por alineamiento de memoria.
- `int endian;`  
  Indica el orden de los bytes en la memoria (little/big endian). Suele ser irrelevante si solo usamos colores básicos y MiniLibX en Linux.

Vamos a "iniciar" el addr de nuestra estructura, yo lo hice en la función init_game que prepara todas las variables antes de los hooks, seguido de una primera impresión de la imagen:

```c
game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
```

¿Para qué sirve `mlx_put_image_to_window`?

Bueno, este es el concepto importante al que me refería, en cada frame nosotros vamos a calcular de qué color ha de ser cada pixel de la pantalla y lo vamos a guardar en el array `data`, este array es como una imagen en la RAM.

- Multiplicamos `y * size_line` → Saltamos todas las filas anteriores.
- Multiplicamos `x * (bpp / 8)` → Nos movemos dentro de la fila actual hasta la columna x.
- Sumamos ambos valores → Obtenemos la posición exacta dentro de `data` donde está ese píxel.

No hace falta que tengamos esto en mente todo el rato, vamos a hacer una función a la que, pasándole la posición x e y del píxel y su color, nos va a colocar dicho píxel en su posición en el array:

```c
void	ft_put_pixel_t(int x, int y, unsigned int color, t_game *game)
{
    char	*dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) // Comprueba que el píxel esté dentro de la pantalla
        return;
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));
    *(unsigned int *) dst = color;
}
```

---

## Pintando mapa

Para que la explicación del raycasting sea más accesible a personas que nunca han oído sobre el tema, vamos a empezar mostrando una vista cenital del mapa.

Yo para esto he creado una función simple para pintar un cuadrado pasándole la posición, el tamaño y el color:

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

Y ahora vas a elaborar una función, que lea la matriz de tu mapa y por cada `1` pinte un cuadrado de un color y por cada `0` un cuadrado de otro color. Yo he utilizado para los muros otra función de...

Esta función que pinta el mapa, llamémosla "draw_map", la vamos a llamar en cada iteración del loop principal, junto con otra que pinte a nuestro player.  
La posición del jugador por ahora va a ser el centro de la pantalla, así que en la estructura player, pondremos su posX y su posY en `width / 2` y `height / 2`. Podemos simplemente utilizar la función...

El loop (muy simplificado) ya debería de ser algo así:

```c
int draw_loop(t_game *game)
{
    t_player *player = &game->player;

    clear_image(game); // Limpiar

    draw_square(player->x, player->y, 10, 0x00FF00, game); // pintar player
    draw_map(game); // pintar mapa
    
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}
```

Vamos a iniciar nuestro juego, y después de quebrarte la cabeza arreglando muchas cosas que no he explicado o que posiblemente hayan salido mal (es el primer intento, no te preocupes) deberías de poder ver...

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/Captura%20desde%202025-09-02%2008-50-09.png?raw=true" alt="Captura de Cub3D" width="400"/>
</p>

---

## Movimiento del player

Para que ese cuadradito pueda moverse vamos a hacer un par de funciones muy simples que ya hemos mencionado antes, `key_press()` y `key_release()`, las cuales hemos pasado a los hooks del teclado.  
Estas funciones no hacen otra cosa que cambiar una serie de booleanos que vamos a incluir en nuestra estructura player, cada uno hará referencia a una tecla, de esta forma nuestra estructura guardará...

Cada vez que pulsamos una tecla, se activará nuestro hook, este generará un "keycode" que hace referencia al código correspondiente a la tecla que se ha pulsado y se lo pasará a la función que le...

```c
mlx_hook(game.win, 2, 1L<<0, key_press, &game.player); // aquí el hook
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

Las constantes `W`, `A`, `S`, `D`... las he guardado en mi archivo .h para no poner ahí los keycode, que son poco intuitivos. En mi caso los keycode son los siguientes:

```c
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
```

La función `key_release()` es igual, pero poniendo las variables a `false`.

Ahora podemos añadir a nuestro loop una función de `move_player()` que va a recalcular en cada frame la posición del jugador.
El movimiento hacia arriba, abajo y los lados es muy sencillo, vamos a crear una constante que será PLAYER_SPEED y dentro de la función de movimiento vamos a decir que "mientras player->key_up == true...

Hazlo así con todas las teclas que tienes guardadas como booleanos en tu estructura player. Al incluir la función `move_player()` antes de las funciones de pintado, ya tendremos esa estructura "básica".

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/ezgif-88233df297ca3c.gif" alt="Captura de Cub3D" width="400"/>
</p>

Para que nuestro juego sea más jugable, nosotros manejamos con `WASD` la posición del jugador y con las flechas de dirección izquierda y derecha; hacia donde "mira" el jugador (movemos su ángulo de vista).  
Para esto necesitamos introducir los conceptos de seno y coseno, que como yo no soy matemático intentaré explicar de la forma menos errónea posible.

Nuestro player va a tener una nueva variable; `angle`. Esta define, a grosso modo, hacia dónde mira el player.

Es común definir la dirección en la que mira el jugador usando un ángulo en radianes.  
Normalmente, se toma el eje X positivo como referencia (mirar a la derecha), y a partir de ahí el ángulo aumenta en sentido antihorario:

- Derecha: 0 radianes (o 2π, es lo mismo)
- Arriba: π/2 radianes
- Izquierda: π radianes
- Abajo: 3π/2 radianes (o -π/2)

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/pi-angles.png" alt="Captura de Cub3D" width="400"/>
</p>

Básicamente, iniciaremos la variable `angle` en una de estas direcciones, dependiendo de hacia donde queremos que mire el player al inicio de la partida.

```html
Guarda una constante de PI en tu .h con unos 12 decimales, lo vamos a utilizar bastante.
```

También vamos a necesitar una constante llamada ANGLE_SPEED, básicamente va a ser la velocidad a la que gira nuestro player, yo la he definido como 0.01. Vamos a sumarle esta cantidad a angle, cada vez que el jugador gire.

```c
if (player->arrow_left)
    player->angle -= angle_speed;
if (player->arrow_right)
    player->angle += angle_speed;
if (player->angle > 2 * PI) // si angle supera a 2 * PI, lo ponemos a 0 y viceversa
    player->angle = 0;
if (player->angle < 0)
    player->angle = 2 * PI;
```

El ángulo al que mira el player va a afectar directamente al movimiento del jugador con las teclas WASD, pues ahora queremos que al pulsar la W, el player se mueva en la dirección que marca el ángulo.

---

### ¿Qué son seno y coseno en este contexto?

Seno (sin) y coseno (cos) son funciones matemáticas que te dicen “cuánto te mueves en X” (horizontal) y “cuánto te mueves en Y” (vertical) cuando quieres avanzar en la dirección hacia donde apuntas.  
Imagina un círculo. El ángulo (`player->angle`) es hacia dónde mira la flecha/jugador.  
Coseno es el movimiento horizontal (X), seno es el movimiento vertical (Y).

¿Para qué sirven aquí?  
Sirven para mover al jugador en la dirección que está mirando, no solo hacia arriba/abajo/izquierda/derecha fijos en la pantalla, sino hacia donde apunta la flecha.

Por ejemplo: Si miras arriba a la derecha, avanzarás en diagonal solo pulsando `W`.

Para moverte hacia adelante y atrás, sumamos o restamos `cos(angle)` para x y `sin(angle)` para y.  
Para el movimiento lateral se invierte y utilizamos `sin(angle)` para x y `cos(angle)` para y:

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

¿Sencillo verdad?  
Ahora vamos a castear nuestro primer rayo en la dirección que tenemos en angle, para hacer más evidente todo lo que hemos implementado hasta el momento.

---

## Casteo de rayos

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
Dibujar la línea es parecido a movernos, vamos a ir pintando píxeles en las posiciones ray_x e y, que van a ir incrementando en la dirección dada por seno y coseno del ángulo pero en vez de depender de una tecla, lo hacemos en cada iteración del bucle.

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

Presta atención a que hemos dividido `px / BLOCK`, ya que px hace referencia a la pantalla que puede ser en mi caso de 576x448, para tener la posición en la matriz, dividimos por el tamaño de nuestra celda.

Una vez implementado esto, nuestro programa debería de verse así, con nuestro primer rayo casteado. A partir de aquí todo toma un poco más de forma y lo vas a entender muy bien.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/ezgif-76bd7f53bd990d.gif" alt="Captura de Cub3D" width="400"/>
</p>

El siguiente paso para entender nuestro algoritmo va a ser lanzar unos cuantos rayos más, para que la explicación sea más visual.

Antes hemos lanzado un rayo en la dirección de angle, como lo que queremos es hacer un arco, vamos a introducir dos variables más y para hacer la prueba vamos a lanzar 10 rayos:

```c
float fraction = PI / 3 / 10; // Esto define la distancia entre cada rayo
float start_x = player->angle - PI / 6; // esto define el ángulo de visión.
```

Voy a explicar un poco mejor lo del ángulo de visión porque así nos liamos un poco:

El ángulo de visión π/3 radianes equivale a 60 grados.

Esto se debe a que para convertir de radianes a grados, multiplicas por 180 y divides entre π:

```html
(π / 3) × (180 / π) = 60°
```
Como nosotros queremos un ángulo de 60º, es decir π / 3, nuestro arco va a comenzar desde angle - (π / 6) y va a ir hasta angle + (π / 6), de esta forma el total es π / 3 quedando al centro el "campo de visión".

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/FOV-img.png" alt="Captura de Cub3D" width="400"/>
</p>

En nuestra prueba con 10 rayos, vamos a sacar el `fraction` (separación entre cada rayo) a partir del campo de visión total (`PI / 3`) dividido entre el número de rayos (`10`) y `start_x` va a ser donde comienza nuestro primer rayo (`PI / 6` como ya hemos explicado antes).

Si nosotros en el loop, en lugar de pintar un rayo desde la posición angle, hacemos un bucle que pinte 10 rayos, desde `start_x` y en cada iteración a start_x le sumamos `fraction`, podremos ver el arco:

```c
while(i < 10)
{
    draw_line(player, game, start_x, i);
    start_x += fraction;
    i++;
}
```
Y aquí el resultado:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/fov-10-rays.gif" alt="Captura de Cub3D" width="400"/>
</p>

Ahora imagina que cogemos cada uno de estos rayos, calculas la distancia que hay hasta que choca con el muro, a partir de esta distancia vas a calcular la altura de esa "línea de píxeles" que corresponde a ese rayo:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/20rays.gif" alt="Captura de Cub3D" width="400"/>
</p>

Y si ahora lanzamos un rayo por cada píxel del ancho de nuestro juego (576px en mi caso) vamos a poder pintar la línea vertical correspondiente a cada uno, consiguiendo una imagen como esta:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/fullwidthrays.gif" alt="Captura de Cub3D" width="400"/>
</p>

---

## Calcular distancia (Raycasting y DDA)

Como puedes observar en el gif de arriba, hay un error cuando comprobamos las colisiones píxel a píxel llamado corner bug, que no reconoce la colisión entre dos celdas pegadas diagonalmente. Por esto se utiliza el algoritmo DDA para el raycasting.

Este algoritmo utiliza la trigonometría para calcular en qué pared choca nuestro rayo.

Vamos a analizar el recorrido de la función draw_line para saber qué estamos haciendo en cada momento:

Primero iniciamos los primeros datos con `ft_init_line_data`:

- En `ft_init_line` calculamos la dirección del rayo con `sen` y `cos`, calculamos la posición relativa del player dentro del mapa y calculamos `delta_dist`.
- `ft_get_delta_dist`: `delta_dist_x` y `delta_dist_y` son la distancia que recorre el rayo entre una línea de un eje y otra del mismo eje, esta es constante:

```c
deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY)
```

Esta fórmula deriva del teorema de Pitágoras, pero se puede simplificar así.

Una vez tenemos delta_dist, necesitamos saber en qué dirección avanzan los "steps" y cuál es la `side_dist` inicial:

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

De esta forma calcularemos si los steps en cada eje avanzarán en +1 o -1, y cuál es la distancia desde el player (que por lo general empezará en una parte intermedia de la celda) hasta el primer eje.

---

Una vez tenemos todos estos datos podemos aplicar el DDA:

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

En cada paso, el rayo avanza a la siguiente línea de celdas (en X o Y) según cuál está más cerca mediante la suma de delta_dist. Cuando choca con una celda que es una pared ('1', 'C', 'D'), termina el bucle. Además, guardamos si side es 0 (ha golpeado el eje x) o 1 (ha golpeado el eje Y).

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/dda_sides.png" height="250"/>
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/dda_gif.gif" height="250"/>
</p>

---

Una vez hemos hecho el algoritmo, podemos calcular la distancia con `ft_get_dist()`:

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

Si observas la imagen de la derecha, verás que cuando estamos viendo una pared de frente, que debería verse recta, la distancia hacia las esquinas es mucho mayor que la distancia en el centro, por eso hacemos esa corrección.

Para calcular esta distancia multiplicamos la distancia perpendicular por el coseno de `ray_angle - player->angle`.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/0RAY_CORRECTION.png" alt="Captura de Cub3D" width="400"/>
</p>

Una vez tenemos la distancia, en `ft_init_line_data()` completamos los datos de la siguiente forma:

```c
d->height = (BLOCK * HEIGHT * SCALE_BLOCK) / d->l.dist;
d->start_y = (HEIGHT - d->height) / 2;
d->end = d->start_y + d->height;
if (d->start_y < 0)
    d->start_y = 0;
if (d->end > HEIGHT)
    d->end = HEIGHT;
```

Siendo SCALE_BLOCK una constante que utilizamos para variar el tamaño de la pared.
start y end será donde empezamos a dibujar la línea vertical, básicamente hacemos el cálculo para que se centre horizontalmente.

---

## Añadir texturas

Vamos a ver nuestra función de `draw_line()`. Aquí ocurren varias cosas.

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

Como ya he dicho antes, esta función va a pintar una línea vertical, habrá tantas líneas como píxeles de ancho tenga nuestro canvas, esta línea se compone de las variables que hemos rellenado en...

Desde y = 0 hasta y = start_y pintamos del color del techo.

Desde start_y hasta end pintaremos la línea de la textura correspondiente, como hemos usado BLOCK = 64 y nuestra textura es también de 64 px, tenemos que averiguar en qué punto exacto golpeó nuestro rayo.

Por último tenemos el color del suelo que irá desde `end` hasta `y = HEIGHT`.

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

Si el rayo golpeó una pared vertical (`side == 0`), calculamos el punto exacto de colisión usando la posición Y del jugador y el componente Y del rayo.  
Si golpeó una pared horizontal (`side == 1`), usamos la posición X del jugador y el componente X del rayo.  
`d->l.dist` es la distancia desde el jugador hasta la pared.  
`d->l.ray_dir_x` y `d->l.ray_dir_y` indican la dirección del rayo.

Ejemplo numérico:  
Supón que el jugador está en `player->y = 100`, el rayo va hacia arriba (`d->l.ray_dir_y = 1.0`), la distancia a la pared (`d->l.dist`) es 32:

```c
d->wall_x = 100 + 32 * 1.0;  // resultado: 132
```

```c
d->wall_x = d->wall_x - floor(d->wall_x / BLOCK) * BLOCK;
```
Aquí calculas la posición exacta del impacto dentro del bloque de la pared.  
Por ejemplo, si tu bloque mide 64 píxeles (`BLOCK=64`) y el impacto fue en x=130, entonces:

- `floor(130 / 64) = 2`
- `2 * 64 = 128`
- `130 - 128 = 2`

Así, wall_x te da el desplazamiento dentro del bloque, que irá de 0 a 63.

De igual manera, para que podamos utilizar texturas que no siempre coincidan con BLOCK, vamos a normalizar el punto, convirtiéndolo en un valor de 0 a 1, de tal manera que si golpea en `x=32`, `tex_x_normalized` será 0.5.

Después vamos a ver cuál de las 4 caras hay que renderizar con `ft_get_wall_c()`, esta función devolverá un int que será el index correspondiente a la textura dentro de nuestro array de texturas.

La siguiente función que viene es esta:

```c
void	ft_calc_texture_data(t_draw_data *d, t_game *game)
{
    d->tex_x = (int)(d->tex_x_normalized * game->textures[d->tex_index].width);
    d->step = 1.0 * game->textures[d->tex_index].height / d->height;
    d->tex_pos = (d->start_y - HEIGHT / 2 + d->height / 2) * d->step;
    d->y = d->start_y;
}
```
Por pasos, aquí vamos a convertir esa cifra normalizada a un punto en el ancho total de la textura:

```c
d->tex_x = (int)(d->tex_x_normalized * game->textures[d->tex_index].width);
```
El "step" indica cuántos píxeles de la textura debes saltar cada vez que pintas un píxel de la pared en la pantalla.  
Si la pared se dibuja más alta que la textura, `step < 1` (la textura se estira). Si se dibuja más baja, `step > 1` (la textura se comprime).

```c
d->step = 1.0 * game->textures[d->tex_index].height / d->height;
```

Calcular la posición inicial en la textura:

```c
d->tex_pos = (d->start_y - HEIGHT / 2 + d->height / 2) * d->step;
```
- `d->start_y` es el primer píxel vertical donde empieza la pared en la pantalla.
- `HEIGHT / 2` es el centro vertical de la ventana/pantalla.
- `d->height / 2` es la mitad de la altura de la pared.

Esta fórmula ajusta la posición inicial (en la textura) para que el mapeo de la textura quede centrado con respecto a la pared dibujada.
Multiplicando por `d->step` conviertes la posición en pantalla a la posición correspondiente en la textura.

Por último vamos a pintar la textura:

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

Hay un punto importante a explicar en cómo se pinta la textura y cómo se hace para comprimirla o expandirla dependiendo de la distancia a la pared.
En el eje x, por ejemplo, si nos situáramos frente a una pared de forma que esta ocupe los 800px del ancho de la pantalla, cada rayo ha golpeado en un px de la pantalla pero también hemos calculado un tex_x distinto para cada columna.
Para el eje y, como ya hemos explicado, se utiliza la variable step, de tal forma que si este es < 1, "repetiremos" píxeles y si es mayor nos los saltaremos.

---

## Shading

Oscurecer el color si es una pared vertical:

```c
if (d->l.side == 0 && !ft_is_light(d->color))
    d->color = (d->color >> 1) & 8355711;
```

En mi caso, para crear un efecto, he elegido que las paredes oeste tendrán como una "Luz" y las paredes este serán una textura con un ligero matiz del color de esta luz para falsear el reflejo de la luz.

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/shading01.png" alt="Captura de Cub3D" width="400"/>
</p>

Puedes ver cómo al oscurecer las paredes verticales y hacer este efecto en las horizontales, tenemos mayor sensación de profundidad. Para favorecer aún más este efecto, podemos añadir un factor que dependa de la distancia a la pared:

```c
unsigned int	ft_get_darkness(unsigned int color, float height)
{
    float			darkness;
    unsigned int	r;
    unsigned int	g;
    unsigned int	b;

    darkness = ((float)height * 0.9) / ((float)HEIGHT * 0.7f); // ajustamos los valores máximo y mínimo
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
Yo he elegido excepciones de colores para que no se oscurezcan, de forma que den la sensación de ser una luz:

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
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/shading02.png" alt="Captura de Cub3D" width="400"/>
</p>

Si ahora añadiéramos textura al suelo y techo, obtendríamos este resultado final:

<p align="center">
  <img src="https://github.com/Nachopuerto95/cub3d/blob/main/img/finalgifbonus.gif" alt="Captura de Cub3D"/>
</p>

---

## <a name="agradecimientos-y-aviso-final"></a>🙏 Agradecimientos y aviso final

> **Gracias por leer.**  
> Esto no pretende ser una guía paso a paso, más bien un apoyo para entender algunas fórmulas matemáticas y ver los principales problemas con los que me he ido topando a la hora de realizar el proyecto Cub3D.
>
> Si el contenido te ha parecido útil, puedes dejar una estrella ⭐️ o un follow.

---
