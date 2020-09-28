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
	
	vec3 world_pos = (Model * vec4(v_position,1)).xyz;	
	vec3 N = normalize( mat3(Model) * v_normal );

	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );

	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float NdotL = dot(N, L);
	float diffuse_light = material_kd * max(NdotL, 0);
	float specular_light = 0;
	if (NdotL > 0)
	{
		specular_light = pow(max(dot(N, H), 0), material_shininess);
	}

	float light = ambient_light + diffuse_light + specular_light;
	// TODO: compute light
	// TODO: send color light output to fragment shader

	float d = distance(world_pos, eye_position);
	const float a = 0.01f, b = 0.02f, c = 1.0f;
	float atten = 1 / (a * d * d + b * d + c);
	color = light * object_color * atten;
	

	
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}