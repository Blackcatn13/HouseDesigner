varying float intensity;
void main()
{
  float PI = 3.14159265358979323864364;
  vec3 pos = gl_ModelViewMatrix * gl_Vertex;
  float cang = dot(pos, gl_LightSource[0].position) / (length(pos) * length(gl_LightSource[0].position));
  float angrad = acos(cang);
  float ang =  (360*angrad) / ( 2 * PI);
  //if(ang < 0) ang = -ang;

  //else intensity = 0.5;
  intensity = (90 - ang) / 90;
  gl_FrontColor = gl_Color;
  gl_Position = ftransform();
}