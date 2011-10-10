#version 120
attribute vec3 vertPosition;
attribute vec3 mycolor;
varying vec3 color;

void main()
{
    gl_Position = vec4( vertPosition, 1.0 );
    color = mycolor;
}
