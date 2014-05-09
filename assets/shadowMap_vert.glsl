varying vec3		N, V, L;
varying vec4		q;
varying vec2		uv;
uniform mat4		shadowTransMatrix;
varying float fogFactor;
void main(void)
{
	vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;
	
    
    
    V = normalize( -eyeCoord.xyz );
	L = normalize( gl_LightSource[0].position.xyz - eyeCoord.xyz );
	N = gl_NormalMatrix * gl_Normal;
    
    
    
	uv =gl_MultiTexCoord0.xy;

	q = shadowTransMatrix *  eyeCoord;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    const float LOG2 = 0.8;
  
	gl_FogFragCoord = length(eyeCoord);
	fogFactor = exp2( -0.0006*
                     0.0006 *
                     gl_FogFragCoord *
                     gl_FogFragCoord *
                     LOG2 );
	fogFactor = clamp(fogFactor, 0.0, 1.0);
}
