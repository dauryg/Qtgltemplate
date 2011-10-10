#version 140

in vec3 vertPosition;
in vec3 vertColor;
out vec4 color;

void main(void)
{
    gl_Position = vec4( vertPosition, 1.0f );
    color = vec4( vertColor, 1.0f );
}
