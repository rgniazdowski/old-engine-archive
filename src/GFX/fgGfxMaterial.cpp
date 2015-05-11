/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxMaterial.h"
#include "Util/fgConfig.h"
#include "Util/fgStrings.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"
#include "GFX/Textures/fgTextureResource.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::SMaterial::SMaterial() :
ambient(1.0f, 1.0f, 1.0f, 1.0f),
diffuse(1.0f, 1.0f, 1.0f, 1.0f),
specular(1.0f, 1.0f, 1.0f, 1.0f),
transmittance(1.0f, 1.0f, 1.0f, 1.0f),
emission(1.0f, 1.0f, 1.0f, 1.0f),
shininess(1.0f),
ior(1.0f),
dissolve(1.0f),
illuminationModel(0),
burn(1.0f),
blendMode(BlendMode::BLEND_OFF),
stateFlags(FRONT_FACE_CCW | DEPTH_TEST | DEPTH_WRITE_MASK | CULL_FACE),
ambientTex(NULL),
diffuseTex(NULL),
specularTex(NULL),
normalTex(NULL),
shaderProgram(NULL),
name(),
shaderName(),
ambientTexName(),
diffuseTexName(),
specularTexName(),
normalTexName(),
unknownParam() { }
//------------------------------------------------------------------------------

size_t gfx::SMaterial::getDataSize(void) {
    size_t size = sizeof (SMaterial);
    size += name.length() +
            ambientTexName.length() +
            diffuseTexName.length() +
            specularTexName.length() +
            normalTexName.length() +
            shaderName.length();
    size += unknownParam.size() * (sizeof (std::string) * 2);
    return size;
}
//------------------------------------------------------------------------------

gfx::SMaterial::SMaterial(const SMaterial& material) {
    this->ambientTex = material.ambientTex;
    this->diffuseTex = material.diffuseTex;
    this->specularTex = material.specularTex;
    this->normalTex = material.normalTex;

    this->name = material.name;
    this->ambient = material.ambient;
    this->diffuse = material.diffuse;
    this->specular = material.specular;
    this->transmittance = material.transmittance;
    this->emission = material.emission;
    this->shininess = material.shininess;
    this->ior = material.ior;
    this->dissolve = material.dissolve;
    this->illuminationModel = material.illuminationModel;
    this->burn = material.burn;
    this->blendMode = material.blendMode;
    this->shaderName = material.shaderName;
    this->shaderProgram = material.shaderProgram;

    this->stateFlags = material.stateFlags;

    this->ambientTexName = material.ambientTexName;
    this->diffuseTexName = material.diffuseTexName;
    this->specularTexName = material.specularTexName;
    this->normalTexName = material.normalTexName;

    this->unknownParam = material.unknownParam;
}
//------------------------------------------------------------------------------

fgBool gfx::SMaterial::loadFromConfig(SMaterial& output, const std::string& path) {
    util::CConfig config;
    if(!config.load(path.c_str())) {
        return FG_FALSE;
    }
    util::SCfgSection *section = config.getSection("Material");
    if(!section) {
        FG_LOG_ERROR("GFX:Material: Couldn't find 'Material' section in: '%s'", path.c_str());
        return FG_FALSE;
    }

    util::config::ParameterVecItor end, itor;
    end = section->parameters.end();
    itor = section->parameters.begin();
    for(; itor != end; itor++) {
        util::SCfgParameter *param = *itor;
        if(!param)
            continue;
        if(param->name.compare("name") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.name = param->string;
            }

        } else if(param->name.compare("ambient") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.ambient = strings::parseColor(param->string);
            }

        } else if(param->name.compare("diffuse") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.diffuse = strings::parseColor(param->string);
            }

        } else if(param->name.compare("specular") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.specular = strings::parseColor(param->string);
            }

        } else if(param->name.compare("transmittance") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.transmittance = strings::parseColor(param->string);
            }

        } else if(param->name.compare("emission") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.emission = strings::parseColor(param->string);
            }

        } else if(param->name.compare("shininess") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                output.shininess = param->float_val;
            } else if(param->type == util::SCfgParameter::INT) {
                output.shininess = (float)param->int_val;
            }

        } else if(param->name.compare("ior") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                output.ior = param->float_val;
            } else if(param->type == util::SCfgParameter::INT) {
                output.ior = (float)param->int_val;
            }

        } else if(param->name.compare("dissolve") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                output.dissolve = param->float_val;
            } else if(param->type == util::SCfgParameter::INT) {
                output.dissolve = (float)param->int_val;
            }

        } else if(param->name.compare("illumination-model") == 0 || param->name.compare("illum-model") == 0) {
            if(param->type == util::SCfgParameter::INT) {
                output.illuminationModel = param->int_val;
            }

        } else if(param->name.compare("burn") == 0) {
            if(param->type == util::SCfgParameter::FLOAT) {
                output.burn = param->float_val;
            } else if(param->type == util::SCfgParameter::INT) {
                output.burn = (float)param->int_val;
            }

        } else if(param->name.compare("ambient-map") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.ambientTexName = param->string;
            }

        } else if(param->name.compare("diffuse-map") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.diffuseTexName = param->string;
            }

        } else if(param->name.compare("specular-map") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.specularTexName = param->string;
            }

        } else if(param->name.compare("normal-map") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.normalTexName = param->string;
            }

        } else if(param->name.compare("shader-name") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                output.shaderName = param->string;
            }

        } else if(param->name.compare("blend-mode") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                // case insensitive
                if(strings::isEqual(param->string, "additive", FG_FALSE)) {
                    output.blendMode = gfx::BlendMode::BLEND_ADDITIVE;
                } else if(strings::isEqual(param->string, "transparency", FG_FALSE)) {
                    output.blendMode = gfx::BlendMode::BLEND_TRANSPARENCY;
                }
            }

        } else if(param->name.compare("front-face") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                if(strings::isEqual(param->string, "ccw", FG_FALSE)) {
                    output.setFrontFace(gfx::FACE_CCW);
                } else if(strings::isEqual(param->string, "cw", FG_FALSE)) {
                    output.setFrontFace(gfx::FACE_CW);
                }
            }

        } else if(param->name.compare("cull-face") == 0) {
            if(param->type == util::SCfgParameter::BOOL) {
                output.setCullFace(param->bool_val);
            } else if(param->type == util::SCfgParameter::INT) {
                output.setCullFace((fgBool)param->int_val);
            }

        } else if(param->name.compare("depth-test") == 0) {
            if(param->type == util::SCfgParameter::BOOL) {
                output.setDepthTest(param->bool_val);
            } else if(param->type == util::SCfgParameter::INT) {
                output.setDepthTest((fgBool)param->int_val);
            }

        } else if(param->name.compare("depth-write-mask") == 0) {
            if(param->type == util::SCfgParameter::BOOL) {
                output.setDepthWriteMask(param->bool_val);
            } else if(param->type == util::SCfgParameter::INT) {
                output.setDepthWriteMask((fgBool)param->int_val);
            }

        } else if(param->name.compare("mtl-reference") == 0) {
            if(param->type == util::SCfgParameter::STRING) {
                // ????
            }
        }
    }
    config.clearAll();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::SMaterial::loadFromConfig(const std::string& path) {
    return self_type::loadFromConfig(*this, path);
}

//------------------------------------------------------------------------------

void gfx::SMaterial::clear(void) {
    // #TODO - here is the place to call resource manager and decrease reference count for the used textures
    //FG_ResourceManager->unlockResource(ambientTexHandle);
    //FG_ResourceManager->unlockResource(diffuseTexHandle);
    //FG_ResourceManager->unlockResource(specularTexHandle);
    //FG_ResourceManager->unlockResource(normalTexHandle);
    // #FIXME #PLOX
    ambientTexName.clear();
    diffuseTexName.clear();
    specularTexName.clear();
    normalTexName.clear();

    name.clear();
    shaderName.clear();
    shaderProgram = NULL;

    ambient = Color4f(0.0f, 0.0f, 0.0f, 1.0f);
    diffuse = Color4f(0.0f, 0.0f, 0.0f, 1.0f);
    specular = Color4f(0.0f, 0.0f, 0.0f, 1.0f);
    transmittance = Color4f(0.0f, 0.0f, 0.0f, 1.0f);
    emission = Color4f(0.0f, 0.0f, 0.0f, 1.0f);

    shininess = 0.0f;
    ior = 0.0f;
    dissolve = 0.0f;
    illuminationModel = 0;
    burn = 0.0f;

    blendMode = BlendMode::BLEND_OFF;

    //stateFlags = FRONT_FACE_CCW | DEPTH_TEST | DEPTH_WRITE_MASK | CULL_FACE;
    stateFlags = NONE;

    ambientTex = NULL;
    diffuseTex = NULL;
    specularTex = NULL;
    normalTex = NULL;

    unknownParam.clear();
}
//------------------------------------------------------------------------------

unsigned int gfx::SMaterial::getSortingValue(const unsigned int maxValue) const {
    unsigned int sortingValue = 0;

    sortingValue += (unsigned int)stateFlags; // 1
    sortingValue += (unsigned int)blendMode; // 2
    if(ambientTex) {
        sortingValue += ambientTex->getRefHandle().getIndex() % 32; // 3
    }
    if(diffuseTex) {
        sortingValue += diffuseTex->getRefHandle().getIndex() % 32; // 4
    }
    if(specularTex) {
        sortingValue += specularTex->getRefHandle().getIndex() % 32; // 5
    }
    if(normalTex) {
        sortingValue += normalTex->getRefHandle().getIndex() % 32; // 6
    }
    sortingValue += (unsigned int)illuminationModel; // 7
    sortingValue += name.length(); // 8

    //if(burn > 1.0f)
    //        burn = 1.0f; // ? ? ?
    sortingValue += (unsigned int)(burn * 10.0f); // 9

    if(sortingValue > maxValue) {
        sortingValue = sortingValue % maxValue;
    }

    return sortingValue;
}
//------------------------------------------------------------------------------
