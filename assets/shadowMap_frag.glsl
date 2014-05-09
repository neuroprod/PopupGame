uniform sampler2DShadow		depthTexture;
uniform sampler2D difTexture;
varying vec2		uv;
varying vec4				q;
varying vec3				N, V, L;
varying float fogFactor;
void main(void)
{

    vec3 normal = normalize( N );
	vec3 R = -normalize( reflect( L, normal ) );
	

	float diffuse = dot( normal, L)*0.5 +0.5;
	float specular = pow(max(dot(R, V), 0.0), 2.0)*0.3;


	vec3 coord = 0.5 * (q.xyz / q.w +1.0);
	float shadow = shadow2D( depthTexture, coord ).r *0.5+0.5;
	
    vec4 color = texture2D(difTexture,uv);
    color.xyz *=diffuse +specular;
    //color.xyz = normal*0.5 +0.5;
    
    gl_FragColor = mix(vec4(0.6,0.7,0.8,1.0), color   * shadow , fogFactor );

	
}
