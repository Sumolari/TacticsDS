---
layout: post
title: Interacción en el tablero
date: 2015-03-03 9:40:00
---

Estamos desarrollando un videojuego basado en un tablero, de modo que éste es el uno de los componentes más importantes, si no el que más.

Tras varias semanas de planificación del tablero y al acabar todos los componentes que necesitábamos para empezar su desarrollo decidimos que teníamos que implementar un API como el siguiente para manejar el tablero:

{% highlight cpp %}
class Grid {

/**
 * Returns cell located at given IndexPath.
 * @param  ip IndexPath, location of the cell.
 * @return    Cell located at given path.
 */
Cell *cellAtIndexPath(IndexPath ip);

/**
 * Returns the currently selected cell's index path.
 * @return Index path of currently selected cell.
 */
IndexPath getSelectedPath();

/**
 * Moves the character in given cell to given cell.
 * @param  from      Original cell of the character.
 * @param  to        Final cell of the character.
 * @param  duration  Duration of the animation.
 * @return           Whether change could be performed or not.
 */
bool moveCharacterFromCellToCell(IndexPath from, IndexPath to,
                                 unsigned int duration);

/**
 * Draws the grid and the cells.
 */
void renderBackground();

/**
 * Draws the characters in the cells.
 */
void renderCharacters();

/**
 * Sets selected cell.
 * If index is out of bounds it'll do nothing and return false.
 * @param  path Path of new selected cell.
 * @return      Whether selected cell changed or not.
 */
bool selectCellAtIndexPath(IndexPath path);

/**
 * Selects cell at bottom of previous cell.
 * If new index is out of bounds it'll do nothing and return false.
 * If no previous cell was selected will return false and do nothing.
 * @return Whether selected cell changed or not.
 */
bool selectBottomCell();

// ... and other helper methods!

}

class Cell {

/**
 * Returns the background type of this cell.
 * @return Background type of this cell.
 */
CellBackgroundType getBackgroundType();

/**
 * Sets background type of this cell to given one.
 * @param type New background type of this cell.
 */
void setBackgroundType(CellBackgroundType type);

/**
 * Returns the position of the center of this cell in the screen.
 * @return Position of the center of this cell in the screen.
 */
FMAW::Point getCenter();

/**
 * Returns whether cell is occupied by a character (true) or not.
 * @return Whether cell is occupied by a character (true) or not.
 */
bool isOccupied();

/**
 * Returns the character occupying this cell.
 * @return Character occupying this cell.
 */
FMAW::Character *getCharacter();

/**
 * Sets the character occupying this cell.
 * @param newCharacter New character that will occupy this cell.
 * @return Previous character occupying this cell.
 */
FMAW::Character *setCharacter(FMAW::Character *newCharacter);

/**
 * Draws this cell's background.
 */
void renderBackground();

/**
 * Draws this cell's character.
 */
void renderCharacter();

}
{% endhighlight %}

Este componente **no** es parte del framework de modo que ahora es cuando se confirma que el diseño del framework es adecuado o no, pero antes veamos por qué hemos decidido diseñar así el tablero.

En primer lugar debemos destacar que estamos trabajando con una consola que a nuestro juicio tiene un hardware muy limitado. No estamos acostumbrados a trabajar con tan sólo 4MB de RAM y los kilobytes no son la unidad de medida que más solemos usar para la memoria, de modo que intentamos reducir el consumo de memoria y de CPU lo máximo posible.

Nuestro juego debe soportar diferentes fondos para las celdas, idealmente texturas para poder imitar escenarios medievales, así que no podemos conformarnos con un color de fondo o incluso con un color por celda.

Decidimos que las celdas debían aprovechar los `backgrounds` que soporta la DS por hardware para dibujar su color de fondo. 

> Uno de los retos de implementar las celdas ha sido que los `backgrounds` se subdividen en `tiles` de 8x8px, una cantidad demasiado pequeña como para ser una celda. Nuestras celdas son de 16x16px de modo que podamos mostrar una textura algo más elaborada. Esto ha requerido bastante trabajo ya que cada celda pasa de ocupar un `tile` fijo a ocupar 4 `tiles` que además no son ni continuados en la memoria (si lo fuesen serían celdas de 32x8px).

Además cada personaje de nuestro juego ocupa una celda (de momento dejemos de lado posibles personajes enormes - dragones o similares - que ocupen varias celdas). Estos personajes deben ser `sprites`, ya que por naturaleza son elementos que se van a mover por la pantalla, van a ser animados como `sprites` y el desarrollo se puede abarcar mediante estos (no hay tantos personajes en juego como celdas).

De modo que una celda tiene un fondo y contiene a un personaje (o no). Además cada celda está situada en unas coordenadas (hemos tomado prestado el concepto de `NSIndexPath` del SDK de iOS). Cada celda conoce las coordenadas de su centro pero no su `IndexPath`, este centro es asignado por el tablero al construir las celdas.

El tablero por su parte debe ofrecer un mecanismo para acceder a las celdas. Para abstraer las coordenadas usamos `IndexPath`. Junto a esto es de agradecer un método auxiliar que haga cómodo mover un personaje de una celda a otra, algo que haremos continuamente.

Además también vendría bien un poco de soporte por parte del tablero para llevar las cuentas de la posición del cursor en cada momento (`selectedCell`).

Todos estos elementos combinados nos permiten crear mapas de forma extraordinariamente sencilla. Por ejemplo, este código genera el mapa del gif animado que hay más adelante:

{% highlight cpp %}
Grid grid;
grid.cellAtIndexPath({3, 6})->setBackgroundType(CellBGMountain);
grid.cellAtIndexPath({4, 4})->setBackgroundType(CellBGRiver);
Warrior warriorA, warriorB;
grid.cellAtIndexPath({0, 0})->setCharacter(&warriorA);
grid.cellAtIndexPath({4, 2})->setCharacter(&warriorB);
grid.renderBackground();
// En el bucle principal.
grid.renderCharacters();
{% endhighlight %}

Nótese que llamamos al método encargado de dibujar los personajes en el bucle principal. Esto es porque el fondo no va a cambiar y por tanto podemos dibujarlo una única vez y olvidarnos de él, sin embargo los personajes sí que van a estar moviéndose y para animarlos y tener al usuario al día del estado del tablero es necesario dibujarlos con más frecuencia.

¿Recordáis aquella [API de interacción de usuario](http://sumolari.github.io/TacticsDS/2015/02/28/Interaccion/) en la que trabajamos previamente? Ahora es cuando entra en juego.

Supongamos que queremos permitir seleccionar un personaje y moverlo a otra casilla. La lógica sería la siguiente:

1. Con las flechas cambio la casilla seleccionada.
1. Con el botón B selecciono al personaje.
1. Con el botón A hago que el personaje seleccionado se desplace a la celda seleccionada.

¿Simple, verdad? ¿Cómo quedaría esto **sin** el API de interacción? Francamente, no queremos ni imaginarnos el jaleo que sería programar eso. Con nuestro framework toda la interacción se reduce a:

{% highlight cpp %}
auto releaseLeftArrow = []() {
    grid.selectLeftCell();
    FMAW::printf("Has soltado la flecha izquierda");
};
FMAW::Input::onButtonArrowLeftReleased(releaseLeftArrow);

auto releaseRightArrow = []() {
    grid.selectRightCell();
    FMAW::printf("Has soltado la flecha derecha");
};
FMAW::Input::onButtonArrowRightReleased(releaseRightArrow);

auto releaseUpArrow = []() {
    grid.selectTopCell();
    FMAW::printf("Has soltado la flecha arriba");
};
FMAW::Input::onButtonArrowUpReleased(releaseUpArrow);

auto releaseDownArrow = []() {
    grid.selectBottomCell();
    FMAW::printf("Has soltado la flecha abajo");
};
FMAW::Input::onButtonArrowDownReleased(releaseDownArrow);

IndexPath pick_up_path = {0, 0};
auto releaseA = [&pick_up_path]() {
    FMAW::printf("Se mueve de %d %d a %d %d",
                 pick_up_path.row,
                 pick_up_path.col,
                 grid.getSelectedPath().row,
                 grid.getSelectedPath().col);
    grid.moveCharacterFromCellToCell(pick_up_path,
                                     grid.getSelectedPath(), 500);
    FMAW::printf("Has soltado la tecla A");
};
FMAW::Input::onButtonAReleased(releaseA);

auto releaseB = [&pick_up_path]() {
    pick_up_path.row = grid.getSelectedPath().row;
    pick_up_path.col = grid.getSelectedPath().col;
    FMAW::printf("Se ha marcado la celda %d %d",
                 pick_up_path.row,
                 pick_up_path.col);
    FMAW::printf("Has soltado la tecla B");
};
FMAW::Input::onButtonBReleased(releaseB);
{% endhighlight %}

¿No estáis algo emocionados viendo la claridad del código? La mayoría del código son `printf` para poder ver en la consola qué casilla está seleccionada (todavía no hemos implementado un indicador visual), además la función más larga tiene menos líneas de código que Frodo Bolsón en su mano derecha. 

> ![Tablero con interacción.](../../../../OtherMedia/grid_1.gif)
>
> Tablero con interacción.

Sin el soporte del framework programar este comportamiento nos habría llevado muchísimo tiempo y requeriría muchísimas líneas de código. Con la ayuda de un framework bien diseñado y un par de clases auxiliares estructuradas con algo de idea se puede lograr el resultado del gif animado con un par de docenas de líneas de código.


