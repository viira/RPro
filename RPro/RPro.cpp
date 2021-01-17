#include "RPro.h"

using namespace std;

int main()
{
    Application a = Application();
    try
    {
        a.launch();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() <<std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
