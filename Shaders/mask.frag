varying vec2 texture_coord;
uniform sampler2D base;
uniform sampler2D over;
uniform sampler2D mask;
uniform sampler2D m1;
uniform sampler2D m2;
uniform sampler2D m3;
uniform sampler2D m4;
uniform vec4 c1;
uniform vec4 c2;
uniform vec4 c3;
uniform vec4 c4;

void main()
{
  vec4 baseColor = texture2D(base, texture_coord);
  vec4 overColor = texture2D(over, texture_coord);
  vec4 m1Color = texture2D(m1, texture_coord) * c1;
  vec4 m2Color = texture2D(m2, texture_coord) * c2;
  vec4 m3Color = texture2D(m3, texture_coord) * c3;
  vec4 m4Color = texture2D(m4, texture_coord) * c4;
  vec4 maskColor = texture2D(mask, texture_coord);

  vec4 finalColor = mix(baseColor, m1Color, maskColor.r);
  finalColor = mix(finalColor, m2Color, maskColor.g);
  finalColor = mix(finalColor, m3Color, maskColor.b);
  finalColor = mix(finalColor, m4Color, maskColor.a);
  finalColor = mix(finalColor, overColor, overColor.a);

  gl_FragColor = finalColor;
}