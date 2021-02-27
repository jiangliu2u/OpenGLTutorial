#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Normal;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec3 a_Color;
out vec3 a_Normal;
out vec3 FragPos;
void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	a_Color = vec3(1.0f, 0.5f, 0.31f);
	FragPos = vec3(model * vec4(position, 1.0));
	a_Normal = mat3(transpose(inverse(model))) * Normal;;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 a_Color;
in vec3 a_Normal;
in vec3 FragPos;
uniform vec3 lightColor;
uniform vec3 lightPos;
void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(a_Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * a_Color;
	color = vec4(result, 1.0);
}