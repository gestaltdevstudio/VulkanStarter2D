#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

layout (location = 0) out vec2 TexCoord;

layout (binding = 0) uniform mvpObj {

	mat4 model;
	mat4 view;
	mat4 proj;

} mvp;

void main()
{
	gl_Position = mvp.proj * mvp.view * mvp.model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
