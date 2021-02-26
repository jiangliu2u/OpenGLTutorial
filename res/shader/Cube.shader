#shader vertex
#version 330 core
layout(location = 0) in vec4 postion;

uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * postion;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;


//uniform vec4 u_Color;
//uniform sampler2D u_Texture;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	color = vec4(0.0, 1.0, 1.0, 1.0);
	//color = u_Color;
}