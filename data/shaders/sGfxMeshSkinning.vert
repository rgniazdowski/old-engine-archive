#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;
varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;

varying highp vec3 v_eye;
#else
//#version 120
varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;
varying vec4 v_color;

varying vec3 v_eye;
#endif

// Matrices
uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;

// Attributes
attribute vec4 a_position; 
attribute vec3 a_normal;
attribute vec2 a_texCoord;
attribute vec3 a_tangent;
attribute vec3 a_bitangent;
attribute vec4 a_blendWeights;
attribute vec4 a_blendIndices;

uniform mat4 u_bones[22];
// boneID:   0     1     2     3
// index:  [0, 1][2, 3][4, 5][6, 7]...
uniform vec4 u_boneDQ[48]; 

vec3 fgQRotate(in vec4 quat, in vec3 p) {
    return p + 2.0 * cross(quat.xyz, cross(quat.xyz, p) + quat.w * p);
}

vec4 fgQRotate(in vec4 quat, in vec4 p) {
    vec4 result;
    result.xyz = p + 2.0 * cross(quat.xyz, cross(quat.xyz, p) + quat.w * p);
    return result;
}

vec4 fgDQTransform(in vec4 dquat[2], in vec4 original) {
        // Translation from the normalized dual quaternion equals :
        // 2.f * qblend_e * conjugate(qblend_0)
        vec3 trans = 2.0 * ( dquat[0].w * dquat[1].xyz -
                             dquat[1].w * dquat[0].xyz +
                             cross(dquat[0].xyz, dquat[1].xyz));

        vec4 tmp;
        // Rotate        
        tmp.xyz = fgQRotate(dquat[0], original.xyz) + trans;
        tmp.w = 1.0;
        return tmp;
}

vec3 fgDQTransform(in vec4 dquat[2], in vec3 original) {
    vec3 trans = 2.0 * ( dquat[0].w * dquat[1].xyz -
                         dquat[1].w * dquat[0].xyz +
                         cross(dquat[0].xyz, dquat[1].xyz));
    return (fgQRotate(dquat[0], original) + trans);
}

vec3 fgDQRotate(in vec4 dquat[2], in vec3 original) { 
    return fgQRotate(dquat[0], original);
}

vec4 fgDQRotate(in vec4 dquat[2], in vec4 original) {    
    return fgQRotate(dquat[0], original);
}

void main()
{
	vec4 blendPos = vec4(0,0,0,0);
	vec4 blendNorm = vec4(0,0,0,0);
	int idxs[4] = int[4](a_blendIndices.x, a_blendIndices.y, a_blendIndices.z, a_blendIndices.w);
	float weights[4] = float[4](a_blendWeights.x, a_blendWeights.y, a_blendWeights.z, a_blendWeights.w);
	int i;
	
	#if 0
	for(i=0;i<4;i++) {
		int idx = idxs[i];
		float weight = weights[i];
		if(i > 0 && idx == 0) // guaranteed that indexes are sorted, can skip;
			break;
		blendPos += (u_bones[idx] * a_position) * weight;		
		blendNorm += u_bones[idx] * vec4(a_normal, 1.0) * weight;
	}
	blendNorm = normalize(blendNorm);
	#endif	
	
	#if 1
	vec4 blendQuat[2];
	vec4 q0;
	for(i=0;i<4;i++) {
        int idx = idxs[i];
        float weight = weights[i];
        if(i > 0 && idx == 0)
            break;
        int iq0 = idx*2;  // rotation part
        int iqe = idx*2+1;// translation part
        if(i == 0) {
            q0 = u_boneDQ[iq0];
            blendQuat[0] = q0 * weight;
            blendQuat[1] = u_boneDQ[iqe] * weight;
            continue;
        }
        if(dot(u_boneDQ[iq0], q0) < 0.0) {
            weight = weight * -1.0;
        }
        blendQuat[0] += u_boneDQ[iq0] * weight; // rot
        blendQuat[1] += u_boneDQ[iqe] * weight; // trans
	}
	float normDQ = length(blendQuat[0]);
	blendQuat[0] /= normDQ;
	blendQuat[1] /= normDQ;	
	blendPos = fgDQTransform(blendQuat, a_position);
	blendNorm.xyz = fgQRotate(blendQuat[0], a_normal);
	#endif 
	
	// Calculate and normalize eye space normal
    vec3 ecNormal = vec3(u_mvMatrix * blendNorm);
    ecNormal = normalize(ecNormal);
    // eye view space
    v_eye = -(u_mvMatrix * a_position);
    
	// Transform the points position by MVP matrix
	gl_Position = u_mvpMatrix * blendPos;
	
	
	// varying position contains original data position
	v_position = blendPos.xyz;
	// Texture coordinate
	v_texCoord = a_texCoord;
	// Normal coordinate
	v_normal = ecNormal;
	// Current color
	v_color = vec4(1.0, 1.0, 1.0, 1.0);
}
