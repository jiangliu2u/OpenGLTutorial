#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
uniform mat4 u_MVP;
out vec3 a_Color;
void main()
{
	gl_Position = u_MVP * vec4(position,1.0f);
	a_Color = color;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 a_Color;
void main()
{
	color = vec4(a_Color, 1.0);
}