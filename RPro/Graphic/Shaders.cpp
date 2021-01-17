#include "Graphic/Shaders.h"

std::vector<char>
Graphic::Shaders::readFile(const std::string filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    //ate for to know size file. This is needed to create the buffer
    if (!file.is_open())
    {
        throw std::runtime_error("readFile in ShaderLoader not success");
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0); // return to the beginning of file
    file.read(buffer.data(), fileSize); // read the entire file
    file.close();

    //std::cout << "size of buffer = " << buffer.size() << std::endl;

    return buffer;
}

VkShaderModule
Graphic::Shaders::createModule(const VkDevice &device,
                               const std::vector<char> &code)
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
    

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateShaderModule not success");
    }
    return shaderModule;
}