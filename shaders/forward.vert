 #version 140
in vec3 vertPosition;
in vec3 mycolor;
out vec3 color;

void main()
{
    gl_Position = vec4( vertPosition, 1.0 );
    color = mycolor;
}
