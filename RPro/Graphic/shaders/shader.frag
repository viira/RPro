#version 460
#extension GL_ARB_separate_shader_objects : enable

//#extension GL_ARB

layout(location = 0) in vec3 flagColor;
layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(flagColor, 1.0);
}
