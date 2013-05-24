varying vec2 texture_coord;
uniform sampler2D base;
uniform sampler2D over;

void main()
{
  texture_coord = vec2(gl_MultiTexCoord0);
  gl_Position = ftransform();
}