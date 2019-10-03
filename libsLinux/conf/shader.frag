#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec2 TexCoord;

// texture sampler
layout(binding = 0) uniform sampler2D texture0;

void main()
{
	FragColor = texture(texture0, TexCoord);
}
