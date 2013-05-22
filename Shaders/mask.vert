varying vec2 texture_coord;
uniform sampler2D base;
uniform sampler2D over;
uniform sampler2D mask;
uniform sampler2D m1;
uniform sampler2D m2;
uniform sampler2D m3;
uniform sampler2D m4;

void main()
{
  texture_coord = vec2(gl_MultiTexCoord0);
  gl_Position = ftransform();
}