---
layout: post
title: Interacción
date: 2015-02-28 9:40:00
---

La Nintendo DS tiene un conjunto finito de botones. De hecho un conjunto mucho más reducido que cualquier teclado. Junto a estos botones dispone de una pantalla táctil que sirve para recibir entrada del usuario, sin embargo hoy vamos a hablar únicamente sobre entrada mediante botones. 

Nuestro objetivo es conseguir un framework que abstraiga por completo la arquitectura de la consola y pueda ser portado fácilmente a otras plataformas, de modo que es imperativo que los mecanismos de LibNDS para gestionar la entrada del usuario queden en una capa inferior y sean totalmente desconocidos para nuestro videojuego.

Tras la buena experiencia con las funciones anónimas de C++11 (véase el [API de animaciones](http://sumolari.github.io/TacticsDS/2015/02/24/Animacion/) y el de [temporizadores](http://sumolari.github.io/TacticsDS/2015/02/16/temporizadores/)) decidimos abarcar este problema con una interfaz similar.

El tutorial sobre [Bouncy Ball](http://ekid.nintendev.com/bouncy/bouncyball.php) incluye un pequeño apartado sobre gestión de la entrada del usuario. Sin embargo como casi todo lo que ofrece por defecto LibNDS es de muy bajo nivel y realmente alejado de lo que podríamos encontrarnos en una plataforma moderna. Ya que tenemos que abstraer el hardware del videojuego, ¿por qué no hacerlo con estilo?

{% highlight cpp %}
void processInput( void )
{
    scanKeys();
    int keysh = keysHeld();
    // process user input
    if( keysh & KEY_UP )      // check if UP is pressed
    {
        // tweak y velocity of ball
        g_ball.yvel -= y_tweak;
    }
    if( keysh & KEY_DOWN )    // check if DOWN is pressed
    {
        // tweak y velocity of ball
        g_ball.yvel += y_tweak;
    }
    if( keysh & KEY_LEFT )    // check if LEFT is pressed
    {
        // tweak x velocity
        g_ball.xvel -= x_tweak;
    }
    if( keysh & KEY_RIGHT )   // check if RIGHT is pressed
    {
        // tweak y velocity
        g_ball.xvel += x_tweak;
    }
}
    
{% endhighlight %}

Si nos fijamos en cómo usa el autor del tutorial la entrada del usuario notaremos diversas cosas:

1. No hay manera de ejecutar código al soltar un botón sin declarar variables auxiliares.
1. No hay manera de ejecutar código únicamente al pulsar el botón (no al mantener) sin declarar variables auxiliares.
1. No hay manera de dejar de ejecutar una respuesta a la pulsación de un botón sin declarar variables auxiliares.
1. ¿Hemos comentado ya algo sobre variables auxiliares?

Seguir con esta aproximación sería una locura a medio plazo. Pensamos en cómo sería la gestión de la entrada en nuestra plataforma ideal y llegamos a este API:

{% highlight cpp %}
//------------------------------------------------------------------------------
// Handling Button Arrow Right.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button ArrowRight is pressed.
 * @param callback  Function to be called when button ArrowRight is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowRightPressed(void (*callback)());

/**
 * Registers a callback so it will be called while button ArrowRight is pressed.
 * @param callback  Function to be called while button ArrowRight is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int whileButtonArrowRightPressed(void (*callback)());

/**
 * Registers a callback so it will be called when button ArrowRight is released.
 * @param callback  Function to be called when button ArrowRight is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowRightReleased(void (*callback)());
/**
 * Unregisters callback with given identifier so it won't be called again.
 * @param identifier Identifier of callback to be unregistered.
 */
bool unregisterCallback(int identifier);
{% endhighlight %}

¿Se ve la idea? **No** más variables auxiliares. **No** más limitaciones. **No** más rodeos para conseguir el objetivo. Un API directa a lo que nos interesa. Sí, suponéis bien pensando que por cada botón disponemos de 3 métodos para añadir un callback. Sí, suponéis bien al pensar que en un futuro cambiaremos el tipo de los parámetros de puntero a función void a función anónima de C++11. 

Pero eso no es lo importante. Lo importante es que ahora podemos tener manejar la entrada del usuario de forma expresiva, clara y limpia:

{% highlight cpp %}
auto pulsaFlechaIzquierda = []() {
    FMAW::printf("Has pulsado la flecha izquierda");
};
FMAW::Input::onButtonArrowLeftPressed(pulsaFlechaIzquierda);

auto mantenFlechaIzquierda = []() {
    FMAW::printf("Mantienes la flecha izquierda pulsada");
};
FMAW::Input::whileButtonArrowLeftPressed(mantenFlechaIzquierda);

auto sueltaFlechaIzquierda = []() {
    FMAW::printf("Has soltado la flecha izquierda");
};
FMAW::Input::onButtonArrowLeftReleased(sueltaFlechaIzquierda);
{% endhighlight %}

Internamente este API utiliza un sistema similar al API de temporizadores. Mantiene una estructura de datos auxiliar con los métodos a llamar para cada botón y estado. Sin embargo en lugar de utilizar el API de temporizadores para gestionar el estado de los botones, utilizamos el bucle principal de juego para llamar a la función del API que comprueba el estado de los botones y llama a los métodos registrados que corresponda.