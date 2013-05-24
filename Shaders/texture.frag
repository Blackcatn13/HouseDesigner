varying vec2 texture_coord;
uniform sampler2D base;
uniform sampler2D over;

void main()
{
  vec4 baseColor = texture2D(base, texture_coord);
  vec4 overColor = texture2D(over, texture_coord);
  vec4 finalColor = mix(baseColor, overColor, overColor.a);
  gl_FragColor = finalColor;
}