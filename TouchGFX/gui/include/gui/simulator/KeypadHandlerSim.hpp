#ifndef __KEYPAD_HANDLER_SIM__
#define __KEYPAD_HANDLER_SIM__
#include <gui/common/keycode.h>
#include <utility>

#define DEFAULT_TICK_TIMEOUT 60

/*
 * Returns a keycode type. This is useful to update UI
 */
typedef enum
{
    OUTPUT_ERROR,
    OUTPUT_NONE,
    OUTPUT_ALPHANUMERIC,
    OUTPUT_ALPHANUMERIC_REPLACE, // Returned only when a letter needs to be deleted and replaced
    OUTPUT_SPECIAL,
    OUTPUT_ACTION
} key_output_t;

/*
 * Available keypad handler states
 */
typedef enum
{
    KEYPADHANDLER_NUMERIC,
    KEYPADHANDLER_FN,
    KEYPADHANDLER_LETTERS,
} keypadhandler_state_t;

class KeypadHandlerSim
{
public:
    KeypadHandlerSim();
    /*
     * Changes the KeypadHandlerSim state. May output a character depending of
     * its state
     */
    std::pair<key_output_t, unsigned char> process_input(unsigned char keycode);

    /*
     * Updates internal tick value. Used for alphanumeric timeout...
     */
    void increase_tick();

private:
    int tick; // Used to store timeout units
    int tick_timeout; // Max ticks before a new letter can be added
    int temp_letter_pos; // Store letter to send...
    unsigned char temp_key;

    /*
     * If true, pressing a button after FN or ABC mode will disable it
     */
    bool disable_special_button_on_input;

    keypadhandler_state_t state; // Default state
    /*
     * Transforms a keyboard input to a compatible keycode
     */
    unsigned char map_char_to_keycode(unsigned char key);

    /*
     * If handler is in KEYPADHANDLER_FN state, returns a special character keycode
     */
    unsigned char map_char_to_special_keycode(unsigned char c);
    /*
     * Mini-state machine that processes letters depending on the timeout
     */
    std::pair<key_output_t, unsigned char> process_async_char(unsigned char c);
    /*
     * Transforms a keypad numeric character to a letter
     */
    static unsigned char map_char_to_letter(unsigned char c, int position);
};

#endif
