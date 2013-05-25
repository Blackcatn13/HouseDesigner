varying vec2 texture_coord;
uniform sampler2D base;
uniform vec4 m1Color;

void main()
{
  vec4 baseColor = texture2D(base, texture_coord);
  vec4 finalColor = mix(baseColor, m1Color, 0.5);
  gl_FragColor = finalColor;
}