varying vec2 texture_coord;

void main()
{
  texture_coord = vec2(gl_MultiTexCoord0);
  gl_Position = ftransform();
}