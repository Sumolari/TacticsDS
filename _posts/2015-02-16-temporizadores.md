---
layout: post
title: Implementando temporizadores
date: 2015-02-16 09:40:00
---

Las limitaciones de hardware siempre son un engorro, y más cuando tienes que hacer conversiones entre las unidades con las que piensas y las unidades con las que trabaja el hardware.

Esta ocasión no iba a ser menos y navegando por la [documentación de libnds](http://libnds.devkitpro.org/) hemos podido comprobar que la consola dispone de 4 relojes en hardware, con un sistema de acceso más bien engorroso.

Aprovechando las posibilidades que ofrece C++ hemos implementado una API para trabajar de forma mucho más cómoda con los relojes:

{% highlight cpp %}

namespace FMAW {

namespace Timer {

/**
 * Inits time subsystem if required.
 */
void init();

/**
 * Enqueues given function so it will be called
 * @param  callback   Function to be called.
 * @param  delta      Time in ms to wait.
 * @param  repetitive Call it over and over again?
 * @return            An identifier to cancel it later.
 */
int enqueue_function(void (*callback)(int),
                     unsigned int delta,
                     bool repetitive);

/**
 * Dequeues given function so it won't called again.
 * @param  id Function to be dequeued.
 * @return    Whether function was dequeued properly or not.
 */
bool dequeue_function(int id);

/**
 * Runs any function that needed to be called.
 */
void check();

}  // namespace Timer

}  // namespace FMAW

{% endhighlight %}

El API cuenta con los métodos `enqueue_function` y `dequeue_function` que nos permiten registrar una función para que se ejecute tras una cierta espera, con posibilidad de seguir llamando a la función hasta que decidamos cancelarla, y de solicitar que se deje de llamar a una función previamente registrada.

Los métodos `init` y `check` se encargan de iniciar el hardware del reloj y de hacer las comprobaciones pertinentes. La función `check` puede ser llamada con seguridad en cualquier momento, ya que no ejecuta ninguna función que no tuviese que ser ejecutada, esto permite que se invoque a `check` tanto desde un reloj implementado en hardware como desde el bucle principal del juego.

Para permitir mayor portabilidad nuestra primera implementación requiere que el programador del juego haga la llamada a `check` en su bucle principal. Nosotros hacemos la llamada antes de dibujar cada frame.

Internamente el API se sostiene en el reloj de hardware que ha iniciado previamente para saber el tiempo transcurrido y si debe o no debe llamar a cada función.

Así quedaría una función `main` básica que actualiza los atributos internos del objeto `g_bug` cada 200 milisegundos:

{% highlight cpp %}
int main(void) {
    FMAW::Timer::init();  // Init timer API.

    auto func = [](int ID) {
        g_bug.update();  // Assuming it was previously declared and initialized.
    };

    FMAW::Timer::enqueue_function(func, 200, true);

    while (1) {
        // Rendering period:
        // Update game objects.
        update_logic();

        // Wait for the vblank period.
        swiWaitForVBlank();

        FMAW::Timer::check();
    }

    return 0;
}
{% endhighlight %}

En las pruebas que hemos realizado no hemos apreciado ninguna sobrecarga. El código queda considerablemente más sencillo que usando los relojes de hardware directamente y nos permite desarrollar una implementación del API independiente para otras plataformas, manteniendo exactamente el mismo código del juego en todas ellas.

