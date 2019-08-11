#shader vertex
#version 330

layout(location = 0) in vec4 position;

uniform mat4 projMatrix;

void main()
{
	gl_Position = projMatrix * position;
}

#shader fragment
#version 330
layout(location = 0) out vec4 colour;

void main()
{
	color = vec4(0f, 0.3f, 0.4f, 1.0f);
}