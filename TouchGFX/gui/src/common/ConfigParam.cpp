#include <gui/common/ConfigParam.hpp>

/**
 * Returns the static vector of parameters. This approach had
 * to be taken to avoid the static initialization fiasco, so instead
 * of initializing a static member using the default way, it is initalized
 * in a static method.
 *
 * @retval vector with all available parameters
 */
std::vector <ConfigParam> & ConfigParam::parameters()
{
    static std::vector<ConfigParam> * out = new std::vector<ConfigParam>;
    return *out;
}