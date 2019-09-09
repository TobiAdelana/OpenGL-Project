#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projection = mat4(1.0);
uniform mat4 view		= mat4(1.0);
uniform mat4 model		= mat4(1.0);

out vec3 frag_pos;
out vec3 frag_normal;
void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	frag_pos = vec3(model * vec4(position, 1.0));
	frag_normal = mat3(transpose(inverse(model))) * normal;

}