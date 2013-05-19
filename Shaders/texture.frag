varying vec2 texture_coord;
uniform sampler2D base;

void main()
{
  gl_FragColor = texture2D(base, texture_coord);
}