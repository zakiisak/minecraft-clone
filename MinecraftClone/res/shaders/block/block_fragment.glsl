#version 330 core

in vec3 fragmentColor;
in vec2 texCoord;
out vec4 color;

uniform sampler2D textureAtlas;

void main() {
    //color = vec4(fragmentColor, 1.0) * texture(textureAtlas, texCoord);
	color = texture(textureAtlas, texCoord);

	//color = vec4(texCoord.x, texCoord.y, 0.0, 1.0);
}