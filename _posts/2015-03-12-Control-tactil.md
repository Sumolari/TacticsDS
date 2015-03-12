---
layout: post
title: Control táctil
date: 2015-03-12 9:40:00
---

El control táctil es una de las formas de interacción con la Nintendo DS y es de hecho la más cómoda para elegir opciones en un menú. Además es fácilmente portable al mundo del PC ya que los clicks del ratón comparten los atributos de posición con los toques en la pantalla táctil. Por tanto nuestro framework debía dar soporte a este tipo de interacción.

Como de costumbre hemos buscado la interfaz forma más cómoda posible para el desarrollador del juego, ignorando lo costoso de implementarla y finalmente hemos abordado y resuelto la implementación interna de la forma más eficiente posible.

Dejaremos de lado los detalles de la implementación interna (que están disponibles en el repositorio del proyecto) y nos centraremos en la interfaz y cómo usarla.

{% highlight cpp %}

namespace FMAW {

namespace Input {

/**
 * Registers a callback that will be called when a touch is detected.
 * Coordinates of the touch will be given as parameters.
 * @param callback  Function to be called. Receives x and y cooordinates of
 *                  touch as parameters.
 * @return Identifier of the callback so it can be registered later.
 */
int onTouchPressed(std::function<void(int, int)> callback);

/**
 * Registers a callback that will be called when a touch is moved.
 * New coordinates of the touch will be given as parameters.
 * @param callback  Function to be called. Receives new x and y cooordinates of
 *                  touch as parameters.
 * @return Identifier of the callback so it can be registered later.
 */
int onTouchMoved(std::function<void(int, int)> callback);

/**
 * Registers a callback that will be called when a touch finishes.
 * Coordinates of the last position of finished touch will be given as
 * parameters.
 * @param callback  Function to be called. Receives x and y cooordinates of
 *                  last position of touch as parameters.
 * @return Identifier of the callback so it can be registered later.
 */
int onTouchReleased(std::function<void(int, int)> callback);

}

}
{% endhighlight %}

¿No es esta interfaz similar a algo que ya se ha comentado en el blog? En efecto, es una extensión del [API de interacción](http://sumolari.github.io/TacticsDS/2015/02/28/Interaccion/) que desarrollamos previamente. De hecho ambas interfaces se declararon a la vez pero hasta hoy no estaban ambas implementadas.

Y bien, ¿qué podemos lograr con esta interfaz? Pues bien, nosotros la hemos usado en el menú principal. Todo el control de la selección del elemento actual del menú se lleva a cabo con estos sencillos métodos:

{% highlight cpp %}

auto touchCallback = [this](int x, int y) {
    if (FMAW::pointInArea({x, y}, MAIN_MENU_NEW_GAME_AREA)) {
        this->currentlySelectedOption = MAIN_MENU_OPTION_NEW_GAME;
    } else if (FMAW::pointInArea({x, y}, MAIN_MENU_LOAD_GAME_AREA)) {
        this->currentlySelectedOption = MAIN_MENU_OPTION_LOAD_GAME;
    } else if (FMAW::pointInArea({x, y}, MAIN_MENU_VERSUS_AREA)) {
        this->currentlySelectedOption = MAIN_MENU_OPTION_VERSUS_GAME;
    }
    this->adjustCurrentTile();
};
this->touchCallbackID = FMAW::Input::onTouchReleased(touchCallback);

auto upArrowCallback = [this]() {
    this->currentlySelectedOption--;
    if (this->currentlySelectedOption < 0) {
        this->currentlySelectedOption += MAIN_MENU_NUM_OPTIONS;
    }
    this->currentlySelectedOption %= MAIN_MENU_NUM_OPTIONS;
    this->menuChangedBackgroundTile = true;
    this->adjustCurrentTile();
};
this->upArrowCallbackID = FMAW::Input::onButtonArrowUpReleased(
                              upArrowCallback);


auto downArrowCallback = [this]() {
    this->currentlySelectedOption++;
    this->currentlySelectedOption %= MAIN_MENU_NUM_OPTIONS;
    this->menuChangedBackgroundTile = true;
    this->adjustCurrentTile();
};
this->downArrowCallbackID = FMAW::Input::onButtonArrowDownReleased(
                                downArrowCallback);


auto aButtonCallback = [this]() {
    FMAW::printf("Selected option %d",
                 this->currentlySelectedOption);
};
this->aButtonCallbackID = FMAW::Input::onButtonAReleased(
                              aButtonCallback);

{% endhighlight %}

> ![Menú interactivo.](http://i.imgur.com/2naHLBT.gifv)
>
> [Menú interactivo](http://i.imgur.com/2naHLBT.gifv).

Cabría destacar que este menú tiene trampa: todo el menú realmente está preprocesado y almacenado como una imagen de 256x192 píxeles. Esta imagen se cambia por la correspondiente a cada posible estado del menú en tiempo de ejecución. 

Habría sido más limpio implementar el menú usando una clase para representar los botones, otra para representar etiquetas de texto, etc, pero nos encontramos ante varios problemas:

1. La Nintendo DS tiene un repertorio muy pequeño de tamaños de Sprite, por lo que un Sprite no sería adecuado para dibujar un botón (serían necesarios varios Sprites por botón y consumiríamos demasiada memoria de Sprites).
1. El soporte de texto tampoco es una maravilla. Cargar fuentes personalizadas y aplicar efectos sobre el texto en tiempo de ejecución podría ser demasiado costoso para el hardware y en cualquier caso un pequeño infierno para abstraer e implementar en el framework.

El menú es realmente uno de los pocos elementos del juego que requiere texto y debido a las limitaciones de tiempo utilizar una imagen preprocesada era la opción más razonable. Sin lugar a dudas si queremos que el framework madure será necesario implementar un módulo de gestión de texto además de un mecanismo mejor para ajustar el fondo de regiones de la pantalla.
