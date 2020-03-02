#version 130


uniform mat4 modelview;
uniform mat4 projection;

in vec2 position;


void main()
{
	gl_Position = projection * modelview * vec4(position, 0.0, 1.0);
}
