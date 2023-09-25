#include <gui/common/ZebraApplication.hpp>

/**
 * Returns the static vector of applications. This approach had
 * to be taken to avoid the static initialization fiasco, so instead
 * of initializing a static member using the default way, it is initalized
 * in a static method.
 *
 * @retval vector with all available applications
 */
std::vector <ZebraApplication> & ZebraApplication::applications()
{
    static std::vector<ZebraApplication> * out = new std::vector<ZebraApplication>;
    return *out;
}