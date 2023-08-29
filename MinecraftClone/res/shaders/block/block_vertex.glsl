#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 fragmentColor;
out vec2 texCoord;

uniform mat4 MVP;

void main(void) {
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	fragmentColor = vertexColor;
	texCoord = aTexCoord;
}
