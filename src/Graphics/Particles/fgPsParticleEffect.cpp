/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of #FLEXIGAME_PROJECT
 *
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgPsParticleEffect.h"

#include <cmath>
#include <cstring>
#include <cstdlib>

#include "fgParticleSystem.h"
#include "../../fgCommon.h"
#include "../../fgMemory.h"
#include "../../Hardware/fgHardwareState.h"

ParticleEffect::~ParticleEffect()
{
    // Love to do destroying manually.. Although it isn't necessary
	m_particles.clear();
    fgArrayVector<Particle> tmpv;
    m_particles.swap( tmpv );

	if(m_colorStream)
		fgFree(m_colorStream);
	if(m_vertStream2D)
		fgFree(m_vertStream2D);
	if(m_vertStream3D)
		fgFree(m_vertStream3D);
	if(m_UVStream)
		fgFree(m_UVStream);
	//if(m_material)
	//	delete m_material; // #FIXME

	m_colorStream = NULL;
	m_vertStream2D = NULL;
	m_vertStream3D = NULL;
	m_UVStream = NULL;
	m_material = NULL;

	m_maxCount = 0;
}

/**
 * Sets m_maxCount, which implies resetting the object
 */
void ParticleEffect::setMaxCount(int max_count)
{
    if( max_count <= 0 ) {
        exit(4);
    }

    // This will fully erase the array
	m_particles.clear();
    fgArrayVector<Particle> tmpv;
    m_particles.swap( tmpv );

    // Prepare for new amount of data
    m_particles.reserve( max_count );
    m_maxCount = max_count;

	if(m_colorStream)
		fgFree(m_colorStream);
	if(m_vertStream2D)
		fgFree(m_vertStream2D);
	if(m_vertStream3D)
		fgFree(m_vertStream3D);
	if(m_UVStream)
		fgFree(m_UVStream);
//if(m_material)
//		delete m_material; // #FIXME

	m_colorStream = NULL;
	m_vertStream2D = NULL;
	m_vertStream3D = NULL;
	m_UVStream = NULL;
	m_material = NULL;

	// #FIXME This allocations need to be in DrawingBatch or SimpleDrawer, need to think about it

	m_colorStream = (fgColor *) fgMalloc(sizeof(fgColor) * 4 * max_count);
	m_vertStream2D = (fgVector2i *) fgMalloc(sizeof(fgVector2i) * 4 * max_count);
	m_vertStream3D = (fgVector3f *) fgMalloc(sizeof(fgVector3f) * 4 * max_count);
	m_UVStream = (fgVector2f *) fgMalloc(sizeof(fgVector2f) * 4 * max_count);
	// #FIXME
	//m_material = new CIwMaterial();
	//m_material->SetCullMode(CIwMaterial::CULL_NONE);
	//m_modelMatrix.SetIdentity();
	//m_emitterOrigin = CIwFVec3::g_Zero;
}

fgBool ParticleEffect::addParameterized(float x, float y, float z, int count)
{
	Particle from, to;
	int i;

	if(count <= 0)
		return FG_FALSE;

	if( int(m_particles.size()) >= maxCount() )
        return FG_FALSE;

	//from.color = m_startColor;
	from.setColor(m_startColor);
	from.data = NULL;
	from.velocity.x = -m_spreadSpeed;
	from.velocity.y = -m_spreadSpeed;
	from.velocity.z = 0.0f;

	from.size = m_startSize;

	// m_lowLife holds life for the particle where value 10.0f is equal to 1000ms TTL
	from.setTTL(m_lowLife/10.0f*1000.0f);

	from.rotation.x = 0.0f;
	from.rotation.y = 0.0f;
	from.rotation.z = 0.0f;

	from.angularVelocity.x = 0.0f;
	from.angularVelocity.y = 0.0f;
	from.angularVelocity.z = 0.0f;

	from.position.x = x;
	from.position.y = y;
	from.position.z = z;

	from.texture_id = 0;


	//to.color = m_startColor;
	to.setColor(m_startColor);
	to.data = NULL;
	to.velocity.x = m_spreadSpeed;
	to.velocity.y = m_spreadSpeed;
	to.velocity.z = 0.0f;

	to.size = m_startSize;

	// m_highLife holds life for the particle where value 10.0f is equal to 1000ms TTL
	to.setTTL(m_highLife/10.0f*1000.0f);

	to.rotation.x = 0.0f;
	to.rotation.y = 0.0f;
	if(m_randomAngle)
		to.rotation.z = 360.0f;
	else
		to.rotation.z = 0.0f;

	to.angularVelocity.x = 0.0f;
	to.angularVelocity.y = 0.0f;
	to.angularVelocity.z = 0.0f;

	to.position.x = x;
	to.position.y = y;
	to.position.z = z;

	to.texture_id = m_textureXSize*m_textureYSize-1;

	for(i=0;i<count;i++)
	{
		if(!addRandom(&from, &to))
			return FG_FALSE;
		if(m_randomVelocity == FG_FALSE)
		{
			int idx = m_particles.size()-1;
			int r = FG_Rand(0,1);
			if(r == 1)
			{
				if(m_particles[idx].velocity.x < 0.0f)
					m_particles[idx].velocity.x = -m_spreadSpeed;
				else
					m_particles[idx].velocity.x = m_spreadSpeed;
			}
			else
			{
				if(m_particles[idx].velocity.y < 0.0f)
					m_particles[idx].velocity.y = -m_spreadSpeed;
				else
					m_particles[idx].velocity.y = m_spreadSpeed;
			}
		}
	}
	return FG_TRUE;
}

void ParticleEffect::calculate(void)
{
	fgArea screenArea;
	screenArea.x = 0;
	screenArea.y = 0;
	screenArea.w = FG_HardwareState->getScreenWidth();
	screenArea.h = FG_HardwareState->getScreenHeight();
	float DT2 = (float)FG_HardwareState->getDelta2();

	for(int i=0; i<int(m_particles.size()); i++)
	{
        // MOVEMENT
		m_particles[i].position.x += m_particles[i].velocity.x/1000.0f * DT2;
		m_particles[i].position.y += m_particles[i].velocity.y/1000.0f * DT2;
		m_particles[i].position.z += m_particles[i].velocity.z/1000.0f * DT2;

        // ROTATION
		m_particles[i].rotation.x += m_particles[i].angularVelocity.x/1000.0f * DT2;
		m_particles[i].rotation.y += m_particles[i].angularVelocity.y/1000.0f * DT2;
		m_particles[i].rotation.z += m_particles[i].angularVelocity.z/1000.0f * DT2;

        // FADE
		m_particles[i].life -= m_particles[i].fade_speed/1000.0f * DT2;

        // LIFE AS SIZE
		if( m_lifeAsSize )
			m_particles[i].size = fabsf( m_particles[i].life );

		// ONLY FOR Z ROTATION
		if( m_facingVelocity )
		{
			float r = sqrt(m_particles[i].velocity.x*m_particles[i].velocity.x + m_particles[i].velocity.y*m_particles[i].velocity.y);
			float a = m_particles[i].velocity.x;
			float b = m_particles[i].velocity.y;
			float sina = b/r;

			double radians = asin(sina);
			float angle = (float)radians/(float)M_PI * 180.0f;

			if(m_drawMode == MODE_2D)
			{
				if(a > 0.0f && b > 0.0f)
					m_particles[i].rotation.z = 90.0f + fabsf(angle);
				else if(a < 0.0f && b > 0.0f)
					m_particles[i].rotation.z = 270.0f - fabsf(angle);
				else if(a < 0.0f && b < 0.0f)
					m_particles[i].rotation.z = 270.0f + fabsf(angle);
				else // if(a > 0.0f && b < 0.0f)
					m_particles[i].rotation.z = 90.0f - fabsf(angle);
			}
			else
			{
				if(a > 0.0f && b > 0.0f)
					m_particles[i].rotation.z = -90.0f - fabsf(angle);
				else if(a < 0.0f && b > 0.0f)
					m_particles[i].rotation.z = 90.0f + fabsf(angle);
				else if(a < 0.0f && b < 0.0f)
					m_particles[i].rotation.z = 90.0f - fabsf(angle);
				else // if(a > 0.0f && b < 0.0f)
					m_particles[i].rotation.z = -(90.0f - fabsf(angle));
			}
		}

		if( m_paramsActive)
		{
			// This actions will work properly only if the particle TTL parameter is set
			// Size
			m_particles[i].size += (m_endSize-m_startSize)/m_particles[i].ttl * DT2;

			/*fgColor color = m_particles[i].color;

			// Color
			color.r += ((float(m_endColor.r-m_startColor.r)/255.0f)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(color.r < 0.0f)
				color.r = 0.0f;
			if(color.r > 1.0f)
				color.r = 1.0f;

			color.g += ((float(m_endColor.g-m_startColor.g)/255.0f)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(color.g < 0.0f)
				color.g = 0.0f;
			if(color.g > 1.0f)
				color.g = 1.0f;

			color.b += ((float(m_endColor.b-m_startColor.b)/255.0f)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(color.b < 0.0f)
				color.b = 0.0f;
			if(color.b > 1.0f)
				color.b = 1.0f;

			color.a += ((float(m_endColor.a-m_startColor.a)/255.0f)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(color.a < 0.0f)
				color.a = 0.0f;
			if(color.a > 1.0f)
				color.a = 1.0f;

			m_particles[i].setColor(color);*/

			/*m_particles[i].color.r += (uint8)((float)(m_endColor.r-m_startColor.r)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(m_particles[i].color.r < 0)
				m_particles[i].color.r = 0;
			if(m_particles[i].color.r > 255)
				m_particles[i].color.r = 255;

			m_particles[i].color.g += (uint8)((float)(m_endColor.g-m_startColor.g)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(m_particles[i].color.g < 0)
				m_particles[i].color.g = 0;
			if(m_particles[i].color.g > 255)
				m_particles[i].color.g = 255;

			m_particles[i].color.b += (uint8)((float)(m_endColor.b-m_startColor.b)/(float)m_particles[i].ttl * FG_HardwareState->DT2());
			if(m_particles[i].color.b < 0)
				m_particles[i].color.b = 0;
			if(m_particles[i].color.b > 255)
				m_particles[i].color.b = 255;

			m_particles[i].color.a += (uint8)(ceilf((float)(m_endColor.a-m_startColor.a)/(float)m_particles[i].ttl * FG_HardwareState->DT2()));
			if(m_particles[i].color.a < 0)
				m_particles[i].color.a = 0;
			if(m_particles[i].color.a > 255)
				m_particles[i].color.a = 255; */
		}

		if( m_particles[i].life <= 0.0f ) {
			remove(i);
		// Checking the particle area which means checking and bouncing off particles of the area edges
		} else if( m_areaSet == true && m_areaCheck == true && m_drawMode == MODE_2D) {
			// Particle X position is within the boundaries so we can check the Y position
			if( m_particles[i].position.x >= float(m_particleArea.x) && m_particles[i].position.x + m_particles[i].size <= float(m_particleArea.x + m_particleArea.w) ) {
				// The UPPER and LOWER boundary
				if( m_particles[i].position.y <= float(m_particleArea.y) || m_particles[i].position.y + m_particles[i].size >= float(m_particleArea.y + m_particleArea.h) )
					m_particles[i].velocity.y *= -1.0f;
			// Particle X position is out of boundaries so we can change it's direction
			} else {
				m_particles[i].velocity.x *= -1.0f;
				// FIXME
			}

			if( m_particles[i].position.y + m_particles[i].size > float(m_particleArea.y + m_particleArea.h) ) {
				float diff = fabsf( float(m_particleArea.y + m_particleArea.h) - (m_particles[i].position.y + m_particles[i].size) );
				m_particles[i].position.y -= diff + m_particles[i].size / 4.0f;
			}

			if( m_particles[i].position.x < float(m_particleArea.x) )
				m_particles[i].position.x += fabsf( m_particles[i].position.x - float(m_particleArea.x) );

			if( m_particles[i].position.x + m_particles[i].size > float(m_particleArea.x+m_particleArea.w) ) {
				float diff = fabsf( float(m_particleArea.x+m_particleArea.w) - (m_particles[i].position.x + m_particles[i].size) );
				m_particles[i].position.x -= diff + m_particles[i].size / 4.0f;
			}
		// Deleting particles fully offscreen
		} else if( m_areaCheck == false && m_drawMode == MODE_2D) {
			if( m_particles[i].position.x + m_particles[i].size/2 >= float(screenArea.x) && m_particles[i].position.x - m_particles[i].size/2 <= float(screenArea.x + screenArea.w) ) {
				// The UPPER and LOWER boundary
				if( m_particles[i].position.y + m_particles[i].size/2 <= float(screenArea.y) || m_particles[i].position.y - m_particles[i].size/2 >= float(screenArea.y + screenArea.h) )
					remove(i);
			// Particle X position is out of boundaries so we can delete it
			} else {
					remove(i);
			}
		}
	}
}

void ParticleEffect::draw(void)
{
	int i = 0;

	static fgVector2f defaultTexCoords[ 4 ] =
	{
		fgVector2f(0.0f, 0.0f),	// 0.x 0.y
		fgVector2f(0.0f, 1.0f),	// 1.x 1.y
		fgVector2f(1.0f, 1.0f),	// 2.x 2.y
		fgVector2f(1.0f, 0.0f),	// 3.x 3.y
	};

	for(i=0; i<int(m_particles.size()); i++)
	{
		int w = m_particles[i].size;
		int h = w;

		// Setting up the particle position
		fgVector2i origin2D;
		origin2D.x = m_emitterOrigin.x + m_particles[i].position.x;
		origin2D.y = m_emitterOrigin.y + m_particles[i].position.y;
		fgVector3f origin3D;
		origin3D = m_particles[i].position + m_emitterOrigin;

		// Setting up the VERTICES STREAM
		if(m_drawMode == MODE_2D) {
			m_vertStream2D[i*4+0] = fgVector2i( -w/2,	-h/2);
			m_vertStream2D[i*4+1] = fgVector2i( -w/2,	 h/2);
			m_vertStream2D[i*4+2] = fgVector2i(  w/2,	 h/2);
			m_vertStream2D[i*4+3] = fgVector2i(  w/2,	-h/2);
		} else {
			m_vertStream3D[i*4+0] = fgVector3f( -w/2,	-h/2, 0.0f);
			m_vertStream3D[i*4+1] = fgVector3f( -w/2,	 h/2, 0.0f);
			m_vertStream3D[i*4+2] = fgVector3f(  w/2,	 h/2, 0.0f);
			m_vertStream3D[i*4+3] = fgVector3f(  w/2,	-h/2, 0.0f);
		}
		if(m_particles[i].texture_id < 0)
			m_particles[i].texture_id = 0;
		if(m_particles[i].texture_id >= m_textureXSize*m_textureYSize)
			m_particles[i].texture_id = 0;
		int x = m_particles[i].texture_id%m_textureXSize;
		int y = m_particles[i].texture_id/m_textureYSize;
		float s  = (float)x/m_textureXSize;
		float t  = (float)y/m_textureYSize;
		float ds = 1.0f/m_textureXSize;
		float dt = 1.0f/m_textureYSize;

		// Setting up the UV STREAM
		m_UVStream[i*4+0] = fgVector2f(s, t);
		m_UVStream[i*4+1] = fgVector2f(s, t+dt);
		m_UVStream[i*4+2] = fgVector2f(s+ds, t+dt);
		m_UVStream[i*4+3] = fgVector2f(s+ds, t);

		// Setting up the COLOR STREAM
		fgColor color = m_particles[i].color;
		m_colorStream[i*4+0] = color;
		m_colorStream[i*4+1] = color;
		m_colorStream[i*4+2] = color;
		m_colorStream[i*4+3] = color;

	/*	if(m_drawMode == MODE_2D) {
			// Setting up the 2D ROTATION
			int rotation = m_particles[i].rotation.z;
			CIwMat2D m;
			m.SetIdentity();
			m.SetRot(IW_ANGLE_FROM_DEGREES(rotation));
			m.SetTrans(origin2D);
			for(uint32 j = 0; j < 4; j++) {
				m_vertStream2D[i*4+j] = m.TransformVec(m_vertStream2D[i*4+j]);
			}
		} else {
			// Setting up the 3D ROTATION
			CIwFMat m;
			CIwFMat rotX, rotY, rotZ;
			m.SetIdentity();
			rotX.SetIdentity();
			rotY.SetIdentity();
			rotZ.SetIdentity();

			rotX.SetRotX(m_particles[i].rotation.x*(float)M_PI/180.0f);
			rotY.SetRotY(m_particles[i].rotation.y*(float)M_PI/180.0f);
			rotZ.SetRotZ(m_particles[i].rotation.z*(float)M_PI/180.0f);
			m.CopyRot(rotX * rotY * rotZ);
			m.SetTrans(origin3D);

			for(uint32 j = 0; j < 4; j++) {
				m_vertStream3D[i*4+j] = m.TransformVec(m_vertStream3D[i*4+j]);
			}
		}	*/
	}
	// PLEASE FIX ME FIX ME FIX ME FIX ME FIX ME
	/*
	// Setting up the material
	IwGxSetMaterial( m_material );

	// Setting up the color stream
	IwGxSetColStream( m_colorStream, int(m_particles.size())*4 );
	// Screen space origin (0,0)
	IwGxSetScreenSpaceOrg( &CIwSVec2::g_Zero );

	// Setting up the vertices stream, in 2D or 3D space
	if(m_drawMode == MODE_2D) {
		IwGxSetVertStreamScreenSpace( m_vertStream2D, int(m_particles.size())*4 );
	} else {
		IwGxSetModelMatrix(&m_modelMatrix);
		IwGxSetVertStreamModelSpace( m_vertStream3D, int(m_particles.size())*4 );
	}

	// Setting up the UV stream
	IwGxSetUVStream(m_UVStream);

	// DRAW
	IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, int(m_particles.size())*4 );

	IwGxSetColStream(NULL);*/
}

/**
 * Takes two particles, does randomization on [from->some_val, to->some_val]
 * and stores new random values to Particle* from
 */
void ParticleEffect::randomizeOnPair(Particle* from, Particle* to, Particle *result)
{
	int from_val, to_val;
    Particle* target = result;

	// Position X
	from_val = (int)(from->position.x*1000);
	to_val = (int)(to->position.x*1000);
	target->position.x = FG_Rand(from_val, to_val)/1000.0f;

	// Position Y
	from_val = (int)(from->position.y*1000);
	to_val = (int)(to->position.y*1000);
	target->position.y = FG_Rand(from_val, to_val)/1000.0f;

	// Position Z
	from_val = (int)(from->position.z*1000);
	to_val = (int)(to->position.z*1000);
	target->position.z = FG_Rand(from_val, to_val)/1000.0f;

	// Velocity X
	from_val = (int)(from->velocity.x*1000);
	to_val = (int)(to->velocity.x*1000);
	target->velocity.x = FG_Rand(from_val, to_val)/1000.0f;

	// Velocity Y
	from_val = (int)(from->velocity.y*1000);
	to_val = (int)(to->velocity.y*1000);
	target->velocity.y = FG_Rand(from_val, to_val)/1000.0f;

	// Velocity Z
	from_val = (int)(from->velocity.z*1000);
	to_val = (int)(to->velocity.z*1000);
	target->velocity.z = FG_Rand(from_val, to_val)/1000.0f;

	// Fade speed
	from_val = (int)(from->fade_speed*1000);
	to_val = (int)(to->fade_speed*1000);
	target->fade_speed = FG_Rand(from_val, to_val)/1000.0f;

	// Life
	from_val = (int)(from->life*1000);
	to_val = (int)(to->life*1000);
	target->life = FG_Rand(from_val, to_val)/1000.0f;

	if(from->ttl != 0 || to->ttl != 0)
	{
		if(from->ttl < to->ttl)
		{
			from_val = from->ttl;
			to_val = to->ttl;
		}
		else
		{
			from_val = to->ttl;
			to_val = from->ttl;
		}
		int ttl = FG_Rand(from_val, to_val);
		target->setTTL(ttl);
	}

	// Size
	from_val = (int)(from->size*1000);
	to_val = (int)(to->size*1000);
	target->size = FG_Rand(from_val, to_val)/1000.0f;

	// Rotation X
	from_val = (int)(from->rotation.x*1000);
	to_val = (int)(to->rotation.x*1000);
	target->rotation.x = FG_Rand(from_val, to_val)/1000.0f;

	// Rotation Y
	from_val = (int)(from->rotation.y*1000);
	to_val = (int)(to->rotation.y*1000);
	target->rotation.y = FG_Rand(from_val, to_val)/1000.0f;

	// Rotation Z
	from_val = (int)(from->rotation.z*1000);
	to_val = (int)(to->rotation.z*1000);
	target->rotation.z = FG_Rand(from_val, to_val)/1000.0f;

	// Angular Velocity X
	from_val = (int)(from->angularVelocity.x*1000);
	to_val = (int)(to->angularVelocity.x*1000);
	target->angularVelocity.x = FG_Rand(from_val, to_val)/1000.0f;

	// Angular Velocity Y
	from_val = (int)(from->angularVelocity.y*1000);
	to_val = (int)(to->angularVelocity.y*1000);
	target->angularVelocity.y = FG_Rand(from_val, to_val)/1000.0f;

	// Angular Velocity Z
	from_val = (int)(from->angularVelocity.z*1000);
	to_val = (int)(to->angularVelocity.z*1000);
	target->angularVelocity.z = FG_Rand(from_val, to_val)/1000.0f;

	// Texture id
	from_val = (int)from->texture_id;
	to_val = (int)to->texture_id;
	target->texture_id = FG_Rand(from_val, to_val);

	// Data
	target->data = NULL;

	// Spawn Time
	target->spawn_time = FG_HardwareState->getTS();

	fgColor color;

	// Color R
	from_val = (int)(from->color.r);
	to_val = (int)(to->color.r);
	color.r = (float)FG_Rand(from_val, to_val)/255.0f;

	// Color G
	from_val = (int)(from->color.g);
	to_val = (int)(to->color.g);
	color.g = (float)FG_Rand(from_val, to_val)/255.0f;

	// Color B
	from_val = (int)(from->color.b);
	to_val = (int)(to->color.b);
	color.b = (float)FG_Rand(from_val, to_val)/255.0f;

	// Color A
	from_val = (int)(from->color.a);
	to_val = (int)(to->color.a);
	color.a = (float)FG_Rand(from_val, to_val)/255.0f;

	target->setColor(color);
}

