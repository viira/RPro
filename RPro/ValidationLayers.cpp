#include "ValidationLayers.h"

using namespace ValidationLayers;

bool
ValidationLayers::checkSupport()
{
    /*
    If validation layers requested for compile - check support,
    else - not check, compile-time error.

    Validation layers can be enabled using the "validation" template parametr
    */
    uint32_t layerCount = 0u;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


    for (const char* name : names)
    {
        bool layerFound = false;

        for (const VkLayerProperties& availableLayer : availableLayers)
        {
            if (strcmp(name, availableLayer.layerName) == 0)
            {
                layerFound = true;

                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }

    }

    return true;
}