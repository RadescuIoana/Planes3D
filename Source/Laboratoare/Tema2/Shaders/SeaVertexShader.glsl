#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_textCoord;
layout(location = 3) in vec3 vertex_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float Time;
uniform vec3 object_color;

out vec3 color;

void main()
{
	// TODO: compute world space vectors
	float random = v_textCoord.y; 
	float angle = v_textCoord.x;
	vec3 position = v_position;
	position.x += cos(Time * random)/30 * cos(angle);
	position.y += cos(Time * random)/30 * sin(angle);

	float c = cos(Time * random)/10;
	color = vec3(0 + c * 7, 0.58 + c * 3, 0.7 + c * 0.3);
	

	
	gl_Position = Projection * View * Model * vec4(position, 1.0);
}