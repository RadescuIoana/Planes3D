#version 330

layout(location = 0) in vec3 v_position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 object_color;

out vec3 color;

void main()
{
	color = object_color;
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}