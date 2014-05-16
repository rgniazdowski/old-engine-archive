/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_GFX_MATERIAL_H_
#define _FG_GFX_MATERIAL_H_

#include <string>

#include "fgGFXTypes.h"
#include "../fgCommon.h"
#include "../fgResource.h"
#include "../fgResourceManager.h"
#include "../Math/fgMathLib.h"

namespace FG_GFX 
{
	// Base structure describing material in graphics rendering
	struct fgGfxMaterial
	{
	public:
		std::string name;

		fgColor4f ambient;
		fgColor4f diffuse;
		fgColor4f specular;
		fgColor4f transmittance;
		fgColor4f emission;
		
		// The shininess parameter of the material
		float shininess;
		// Index of refraction parameter
		float ior;
		// The dissolve parameter of the material
		float dissolve;           // 1 == opaque; 0 == fully transparent
		// Illumination model (see http://www.fileformat.info/format/material/)
		int illuminationModel;

		// Name of the ambient texture
		std::string ambientTexName;
		// Name of the diffuse texture
		std::string diffuseTexName;
		// Name of the specular texture
		std::string specularTexName;
		// Name of the normal texture
		std::string normalTexName;

		//std::map<std::string, std::string> unknown_parameter; // #FIXME
		// Handle for the ambient texture
		FG_RHANDLE ambientTexHandle;
		// Handle for the diffuse texture
		FG_RHANDLE diffuseTexHandle;
		// Handle for the specular texture
		FG_RHANDLE specularTexHandle;
		// Handle for the normal texture
		FG_RHANDLE normalTexHandle;

		fgGfxMaterial()
		{
			ambientTexHandle = FG_INVALID_RHANDLE;
			diffuseTexHandle = FG_INVALID_RHANDLE;
			specularTexHandle = FG_INVALID_RHANDLE;
			normalTexHandle = FG_INVALID_RHANDLE;

			ambientTexName.clear();
			diffuseTexName.clear();
			specularTexName.clear();
			normalTexName.clear();
		}

		~fgGfxMaterial()
		{
			clear();
		}

		void clear(void)
		{
			// #TODO - here is the place to call resource manager and decrease reference count for the used textures
			// #TODO - ! remember to change the whole reference mechanism to be more automatic (if its even possible)
			FG_ResourceManager->unlockResource(ambientTexHandle);
			FG_ResourceManager->unlockResource(diffuseTexHandle);
			FG_ResourceManager->unlockResource(specularTexHandle);
			FG_ResourceManager->unlockResource(normalTexHandle);

			ambientTexName.clear();
			diffuseTexName.clear();
			specularTexName.clear();
			normalTexName.clear();
		}
	};

};

#endif /* _FG_GFX_MATERIAL_H_ */