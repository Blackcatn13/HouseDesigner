varying vec2 texture_coord;
uniform sampler2D base;

void main()
{
  texture_coord = vec2(gl_MultiTexCoord0);
  gl_Position = ftransform();
}