---
layout: post
title: Animación
date: 2015-02-24 9:40:00
---

La capacidad de animar los personajes del juego es imprescindible. Implementar manualmente las animaciones es un pequeño infierno si no se hace de forma organizada, y coordinar muchas animaciones es una receta segura para el desastre si no se es ordenado.

Nosotros creemos ser ordenados pero también somos lo suficientemente avispados como para saber que es mejor hacemos que el framework nos ayude a ser ordenados que confiar en nuestro instinto organizativo. Así nacen tanto la clase `Character` como los métodos de animación.

La clase `Character` representa todos los objetos que en la DS se muestran en pantalla mediante `Sprites`, esto es, cualquier cosa que se muestra en pantalla y no es un `background`. Por tanto un `Character` necesita almacenar información sobre el `Sprite` con el que se dibujará y su posición en la pantalla.

Además de con los métodos necesarios para manipular los atributos del objeto, contamos con 4 métodos de animación: {% highlight cpp %}
/**
 * Moves this character to given position animatedly.
 * @param position Final position of the character.
 * @param duration Time it'll take to move the character.
 * @return         Identifier of the animation that will be performed.
 */
animation_id animateToPosition(Point position, unsigned int duration);

/**
 * Moves this character to given position animatedly.
 * @param position Final position of the character.
 * @param duration Time it'll take to move the character.
 * @param callback Function that will be called when animation finishes.
 *                 It'll receive whether animation finished successfully
 *                 (true) or not (false).
 */
animation_id animateToPosition(Point position, unsigned int duration,
                               std::function<void(bool)> callback);

/**
 * Moves this character to given position animatedly.
 * @param position Final position of the character.
 * @param duration Time it'll take to move the character.
 * @param type     Type of animation to be performed.
 * @param callback Function that will be called when animation finishes.
 *                 It'll receive whether animation finished successfully
 *                 (true) or not (false).
 */
animation_id animateToPosition(Point position, unsigned int duration,
                               AnimationType type,
                               std::function<void(bool)> callback);

/**
 * Cancels animation with given ID.
 * @param  id ID of animation to cancel.
 * @return    Whether animation was cancelled or not.
 */
bool cancelAnimation(animation_id id);    
{% endhighlight %}

Actualmente el framework únicamente soporta animación de las coordenadas del `Character`, además mediante interpolación lineal, aunque está preparado para que en un futuro se implementen otras funciones de interpolación.

El primer método de animación permite animar el cambio de posición del personaje, dada la nueva posición y la duración de la animación. Un segundo método permite especificar un callback que se llamará al terminar la animación, ya sea correctamente o se haya cancelado. El tercer método permite especificar además la función de interpolación (aunque actualmente sólo haya una). El último método permite cancelar una animación previamente iniciada, dejando al personaje en la posición en la que se hubiese quedado.

La implementación de las animaciones puede que sea lo más interesante. Internamente utilizamos una estructura `Animation` para almacenar toda la información necesaria para llevar a cabo la animación:

{% highlight cpp %}
typedef struct t_animation {
    /**
     * ID of this callback.
     */
    int ID;
    /**
     * ID of this callback when registered with Timer API.
     */
    int callback_id;
    /**
     * Position of the Character when animation started.
     */
    Point initialPosition;
    /**
     * Final position of the Character.
     */
    Point finalPosition;
    /**
     * Duration of the animation, in milliseconds.
     */
    unsigned int duration;
    /**
     * Remaining duration of the animation, in milliseconds.
     */
    unsigned int remainingDuration;
    /**
     * Type of animation to perform.
     */
    AnimationType type;
    /**
     * Callback to be called when animation is finished.
     */
    std::function<void(bool)> callback;
} Animation;
{% endhighlight %}

Como puede deducirse por esta estructura el API de animaciones utiliza [el API de temporizadores](http://sumolari.github.io/TacticsDS/2015/02/16/temporizadores/). Encola una función que comprueba el tiempo transcurrido y calcula la posición en la que debería estar el personaje aplicando la interpolación correspondiente. Cuando la animación termina se desencola la función de animación y se llama al callback si está definido.

Realmente nos alegra ver cómo trabajo previo sirve de pilares para funciones que parecen muy complejas pero que gracias a unos cimientos sólidos en el framework su implementación es coser y cantar.