#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;
varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;

varying highp vec3 v_eye;
#else

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;
varying vec4 v_color;

varying vec3 v_eye;
#endif

// Light
uniform SDirectionalLight u_directionalLight;
// Material
uniform SMaterial u_material;
// Diffuse texture
uniform sampler2D s_texture;
// Whether or not to use texture color
uniform float u_useTexture;

void main() { 
    vec4 texel;
    if(u_useTexture > 0.5) {
		texel = texture2D(s_texture, v_texCoord);
	} else {
		texel = v_color;
		
	}
    ////////////////////////////////////
    
    // set the specular term to black
    vec4 spec = vec4(0.0);
 
    // normalize both input vectors
    vec3 n = normalize(v_normal);
    vec3 e = normalize(v_eye);
 
    float intensity = max(dot(n,u_directionalLight.direction), 0.0);
    // Calculate ambient light
    vec4 ambientColor = u_directionalLight.ambient * u_material.ambient;
    // Calculate diffuse light
    vec4 diffuseColor = u_directionalLight.diffuse * u_material.diffuse;
    
    // if the vertex is lit compute the specular color
    if (intensity > 0.0) {
        // compute the half vector
        vec3 h = normalize(u_directionalLight.direction + e);  
        // compute the specular term into spec
        float intSpec = max(dot(h,n), 0.0);
        spec = u_material.specular * pow(intSpec, u_material.shininess) * u_directionalLight.specular;
    }
    
    gl_FragColor = max(intensity * diffuseColor + spec, ambientColor) * texel;
}
