#ifndef FMAW_INPUT_H
#define FMAW_INPUT_H

namespace FMAW {

namespace Input {

#define BUTTONS_COUNT 10
#define BUTTONS {ButtonA, ButtonB, ButtonSelect, ButtonStart, ButtonL, ButtonR,\
        ButtonArrowUp, ButtonArrowDown, ButtonArrowLeft, ButtonArrowRight }

typedef enum BUTTONS ButtonType;

//------------------------------------------------------------------------------
// Handling Button A.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button A is pressed.
 * @param callback  Function to be called when button A is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonAPressed(void (*callback));

/**
 * Registers a callback so it will be called when button A is released.
 * @param callback  Function to be called when button A is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonAReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button B.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button B is pressed.
 * @param callback  Function to be called when button B is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonBPressed(void (*callback));

/**
 * Registers a callback so it will be called when button B is released.
 * @param callback  Function to be called when button B is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonBReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button L.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button L is pressed.
 * @param callback  Function to be called when button L is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonLPressed(void (*callback));

/**
 * Registers a callback so it will be called when button L is released.
 * @param callback  Function to be called when button L is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonLReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button R.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button R is pressed.
 * @param callback  Function to be called when button R is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonRPressed(void (*callback));

/**
 * Registers a callback so it will be called when button R is released.
 * @param callback  Function to be called when button R is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonRReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button Select.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button Select is pressed.
 * @param callback  Function to be called when button Select is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonSelectPressed(void (*callback));

/**
 * Registers a callback so it will be called when button Select is released.
 * @param callback  Function to be called when button Select is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonSelectReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button Start.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button Start is pressed.
 * @param callback  Function to be called when button Start is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonStartPressed(void (*callback));

/**
 * Registers a callback so it will be called when button Start is released.
 * @param callback  Function to be called when button Start is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonStartReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button Arrow Up.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button ArrowUp is pressed.
 * @param callback  Function to be called when button ArrowUp is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowUpPressed(void (*callback));

/**
 * Registers a callback so it will be called when button ArrowUp is released.
 * @param callback  Function to be called when button ArrowUp is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowUpReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button Arrow Down.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button ArrowDown is pressed.
 * @param callback  Function to be called when button ArrowDown is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowDownPressed(void (*callback));

/**
 * Registers a callback so it will be called when button ArrowDown is released.
 * @param callback  Function to be called when button ArrowDown is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowDownReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button Arrow Left.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button ArrowLeft is pressed.
 * @param callback  Function to be called when button ArrowLeft is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowLeftPressed(void (*callback));

/**
 * Registers a callback so it will be called when button ArrowLeft is released.
 * @param callback  Function to be called when button ArrowLeft is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowLeftReleased(void (*callback));

//------------------------------------------------------------------------------
// Handling Button Arrow Right.
//------------------------------------------------------------------------------

/**
 * Registers a callback so it will be called when button ArrowRight is pressed.
 * @param callback  Function to be called when button ArrowRight is pressed.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowRightPressed(void (*callback));

/**
 * Registers a callback so it will be called when button ArrowRight is released.
 * @param callback  Function to be called when button ArrowRight is released.
 * @return Identifier of the callback so it can be registered later.
 */
int onButtonArrowRightReleased(void (*callback));

//------------------------------------------------------------------------------
// Callback handling.
//------------------------------------------------------------------------------

/**
 * Checks if any button has been pressed and calls proper method.
 */
void check();

/**
 * Unregisters callback with given identifier so it won't be called again.
 * @param identifier Identifier of callback to be unregistered.
 */
bool unregisterCallback(int identifier);

}

}

#endif