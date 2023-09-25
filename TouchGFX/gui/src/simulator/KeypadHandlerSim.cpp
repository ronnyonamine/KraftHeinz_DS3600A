#ifdef SIMULATOR

#include <gui/simulator/KeypadHandlerSim.hpp>

#define ABC_KEYBOARD_CHAR (unsigned char) 'q'
#define FN_KEYBOARD_CHAR (unsigned char) 'e'

#define UP_KEYBOARD_CHAR (unsigned char) 'w'
#define DOWN_KEYBOARD_CHAR (unsigned char) 's'
#define LEFT_KEYBOARD_CHAR (unsigned char) 'a'
#define RIGHT_KEYBOARD_CHAR (unsigned char) 'd'

#define HOME_KEYBOARD_CHAR (unsigned char) 'z'
#define ENTER_KEYBOARD_CHAR (unsigned char) 'x'
#define BACKSPACE_KEYBOARD_CHAR (unsigned char) 'c'

#define ZERO_KEYBOARD_CHAR (unsigned char) '0'

#define KEYPAD_2_GROUP_ARRAY "abcABC"
#define KEYPAD_3_GROUP_ARRAY "defDEF"
#define KEYPAD_4_GROUP_ARRAY "ghiGHI"
#define KEYPAD_5_GROUP_ARRAY "jklJKL"
#define KEYPAD_6_GROUP_ARRAY "mnoMNO"
#define KEYPAD_7_GROUP_ARRAY "pqrsPQRS"
#define KEYPAD_8_GROUP_ARRAY "tuvTUV"
#define KEYPAD_9_GROUP_ARRAY "wxyzWXYZ"

const char keypad_groups[8][9] = {
    KEYPAD_2_GROUP_ARRAY,
    KEYPAD_3_GROUP_ARRAY,
    KEYPAD_4_GROUP_ARRAY,
    KEYPAD_5_GROUP_ARRAY,
    KEYPAD_6_GROUP_ARRAY,
    KEYPAD_7_GROUP_ARRAY,
    KEYPAD_8_GROUP_ARRAY,
    KEYPAD_9_GROUP_ARRAY
};

KeypadHandlerSim::KeypadHandlerSim() { }

std::pair<key_output_t, unsigned char> KeypadHandlerSim::process_input(unsigned char c)
{
    unsigned char compatible_keycode = map_char_to_keycode(c);

    if(compatible_keycode == 255)
    {
        return std::make_pair(OUTPUT_ERROR, -1);
    }

    switch(state)
    {
        case KEYPADHANDLER_NUMERIC:
            if((compatible_keycode >= '0') && (compatible_keycode <= '9'))
            {
                // Entered numeric value... keep state
                return std::make_pair(OUTPUT_ALPHANUMERIC, c);
            }
            if (compatible_keycode == KEYCODE_BLUE)
            {
                // Pressed special button (FN)... Change state to F
                state = KEYPADHANDLER_FN;
                return std::make_pair(OUTPUT_SPECIAL, compatible_keycode);
            }
            if(compatible_keycode == KEYCODE_GREEN)
            {
                // Pressed letter special button
                state = KEYPADHANDLER_LETTERS; 
                return std::make_pair(OUTPUT_SPECIAL, compatible_keycode);
            }
           
            // Pressed action character (enter, backspace, home, arrows).
            // Don't change state...
            return std::make_pair(OUTPUT_ACTION, compatible_keycode);
            
        case KEYPADHANDLER_FN:
            /* 
             * Special function activated. Next input will decide which 
             * button to press 
             */
            if(compatible_keycode == KEYCODE_BLUE)
            {
                // Go back to initial numeric state...
                state = KEYPADHANDLER_NUMERIC;
                return std::make_pair(OUTPUT_SPECIAL, compatible_keycode);
            }
            if(compatible_keycode == KEYCODE_GREEN)
            {
                // Go back to initial numeric state...
                state = KEYPADHANDLER_LETTERS;
                return std::make_pair(OUTPUT_SPECIAL, compatible_keycode);
            }
			if((compatible_keycode == KEYCODE_UP)    ||
			   (compatible_keycode == KEYCODE_DOWN)  ||
			   (compatible_keycode == KEYCODE_LEFT)  ||
			   (compatible_keycode == KEYCODE_RIGHT) ||
			   (compatible_keycode == KEYCODE_ENTER)  )
			{
				return std::make_pair(OUTPUT_ACTION, compatible_keycode);
			}
            // Ignore initial map since this is a special character
            return std::make_pair(OUTPUT_SPECIAL, map_char_to_special_keycode(c));

        case KEYPADHANDLER_LETTERS:
            if(compatible_keycode == KEYCODE_GREEN)
            {
                // Go back to initial numeric state...
                state = KEYPADHANDLER_NUMERIC;
                return std::make_pair(OUTPUT_SPECIAL, compatible_keycode);
            }
            if(compatible_keycode == KEYCODE_BLUE)
            {
                // Go back to initial numeric state...
                state = KEYPADHANDLER_FN;
                return std::make_pair(OUTPUT_SPECIAL, compatible_keycode);
            }
			if((compatible_keycode == KEYCODE_UP)    ||
			   (compatible_keycode == KEYCODE_DOWN)  ||
			   (compatible_keycode == KEYCODE_LEFT)  ||
			   (compatible_keycode == KEYCODE_RIGHT) ||
			   (compatible_keycode == KEYCODE_ENTER) ||
			   (compatible_keycode == KEYCODE_HOME) ||
			   (compatible_keycode == KEYCODE_BKSP)  )
			{
				return std::make_pair(OUTPUT_ACTION, compatible_keycode);
			}
            if(compatible_keycode == '1')
            {
                // Ignore 1 since it doesn't have any letterimplementation
                break;
            }
            if((compatible_keycode >= '0') && (compatible_keycode <= '9'))
            {
                // Generate an alphanumeric value. Ignore remaining buttons
                return process_async_char(compatible_keycode);
            }
            break;
        default:
            /* Invalid key pressed or not supported */
            break;
            
    }
    return std::make_pair(OUTPUT_ERROR, -1);
}

void KeypadHandlerSim::increase_tick()
{
    tick++;
}

std::pair<key_output_t, unsigned char> KeypadHandlerSim::process_async_char(unsigned char c)
{
    if((tick > tick_timeout) // Timeout expired
       || temp_key != c // Change letter
       || c == '0')  // 0 doesn't contain letters
    {
        // Send the first letter and reset tick counter...
        tick = 0;
        temp_letter_pos = 0;
        temp_key = c;

        return std::make_pair(OUTPUT_ALPHANUMERIC, map_char_to_letter(c, temp_letter_pos));
    }
    else
    {
        // We are in time... Send a request to replace the last letter
        tick = 0;
        if(map_char_to_letter(c, ++temp_letter_pos) == 0)
        {
            // Reached the end of the group... Start from begining.
            temp_letter_pos = 0;
        }
        temp_key = c;

        return std::make_pair(OUTPUT_ALPHANUMERIC_REPLACE, map_char_to_letter(c, temp_letter_pos));
    }
}

unsigned char KeypadHandlerSim::map_char_to_letter(unsigned char c, int position)
{
    if(c == '0')
    {
        // 0 key is the only that doesn't contain letters... return space directly
        return ' ';
    }
    return keypad_groups[c-50][position];
}

unsigned char KeypadHandlerSim::map_char_to_special_keycode(unsigned char c)
{
    switch(c)
    {
        case BACKSPACE_KEYBOARD_CHAR:
            return KEYCODE_ESC;
        case HOME_KEYBOARD_CHAR:
            return KEYCODE_INC;
        case ZERO_KEYBOARD_CHAR:
            return KEYCODE_DEC;
        default:
            if((c > '0') && (c <= '9'))
            {
                // Do not include 0 since itself is another special keycode

            }
    }
    return -1;
}

unsigned char KeypadHandlerSim::map_char_to_keycode(unsigned char c)
{
    switch(c)
    {
        case ABC_KEYBOARD_CHAR:
            return KEYCODE_GREEN;
        case FN_KEYBOARD_CHAR:
            return KEYCODE_BLUE;
        case HOME_KEYBOARD_CHAR:
            return KEYCODE_HOME;
        case ENTER_KEYBOARD_CHAR:
            return KEYCODE_ENTER;
        case BACKSPACE_KEYBOARD_CHAR:
            return KEYCODE_BKSP;
        case UP_KEYBOARD_CHAR:
            return KEYCODE_UP;
        case LEFT_KEYBOARD_CHAR:
            return KEYCODE_LEFT;
        case DOWN_KEYBOARD_CHAR:
            return KEYCODE_DOWN;
        case RIGHT_KEYBOARD_CHAR:
            return KEYCODE_RIGHT;
        default:
            /*
             * Ignores any other keyboard character
             */
            if((c >= '0') && (c <= '9'))
            {
                // Numeric keypad
                return c;
            }
            else
            {
                return -1;
            }
    }
}

#endif
