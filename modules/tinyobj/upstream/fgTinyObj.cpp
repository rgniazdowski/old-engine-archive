//
// Copyright 2012-2013, Syoyo Fujita.
// 
// Licensed under 2-clause BSD license (Simplified BSD)
//

//
// Required:   License and copyright notice
// 
// Permitted:  Commercial Use
//             Distribution
//             Modification
//             Private Use
//             Sublicensing
// 
// Forbidden:  Hold Liable

//
// version 0.9.6: Support Ni(index of refraction) mtl parameter.
//                Parse transmittance material parameter correctly.
// version 0.9.5: Parse multiple group name.
//                Add support of specifying the base path to load material file.
// version 0.9.4: Initial suupport of group tag(g)
// version 0.9.3: Fix parsing triple 'x/y/z'
// version 0.9.2: Add more .mtl load support
// version 0.9.1: Add initial .mtl load support
// version 0.9.0: Initial
//

//
// Changes made in code to make it more compatible with FG engine.
// Usage of FG types for material, vertex, etc
//

#include <cstdlib>
#include <cstring>
#include <cassert>

#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "fgTinyObj.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"
#include "Util/fgStringParser.h"

namespace fgTinyObj {

    /**
     * 
     * @param material
     */
    void InitMaterial(fg::gfx::SMaterial& material) {
        material.name = "";
        material.ambientTexName = "";
        material.diffuseTexName = "";
        material.specularTexName = "";
        material.normalTexName = "";
        for(int i = 0; i < 3; i++) {
            material.ambient[i] = 0.f;
            material.diffuse[i] = 0.f;
            material.specular[i] = 0.f;
            material.transmittance[i] = 0.f;
            material.emission[i] = 0.f;
        }
        material.illuminationModel = 0;
        material.dissolve = 1.f;
        material.shininess = 1.f;
        material.ior = 1.f;
        material.unknownParam.clear();
    }

    /**
     *
     */
    struct vertex_index
    {
        int v_idx, vt_idx, vn_idx;

        vertex_index() { };

        vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx) { };

        vertex_index(int vidx, int vtidx, int vnidx) : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx) { };

    };

    // for std::map

    static inline bool operator <(const vertex_index& a, const vertex_index& b) {
        if(a.v_idx != b.v_idx) return (a.v_idx < b.v_idx);
        if(a.vn_idx != b.vn_idx) return (a.vn_idx < b.vn_idx);
        if(a.vt_idx != b.vt_idx) return (a.vt_idx < b.vt_idx);

        return false;
    }

    //struct obj_shape {
    //  fgVector<float> v;
    //  fgVector<float> vn;
    //  fgVector<float> vt;
    //};

    static inline bool isSpace(const char c) {
        return (c == ' ') || (c == '\t');
    }

    static inline bool isNewLine(const char c) {
        return (c == '\r') || (c == '\n') || (c == '\0');
    }

    // Make index zero-base, and also support relative index. 

    static inline int fixIndex(int idx, int n) {
        int i;

        if(idx > 0) {
            i = idx - 1;
        } else if(idx == 0) {
            i = 0;
        } else { // negative value = relative
            i = n + idx;
        }
        return i;
    }

    static inline std::string parseString(const char*& token) {
        std::string s;
        int b = strspn(token, " \t");
        int e = strcspn(token, " \t\r");
        s = std::string(&token[b], &token[e]);

        token += (e - b);
        return s;
    }

    static inline int parseInt(const char*& token) {
        token += strspn(token, " \t");
        int i = atoi(token);
        token += strcspn(token, " \t\r");
        return i;
    }

    static inline float parseFloat(const char*& token) {
        token += strspn(token, " \t");
        float f = (float)atof(token);
        token += strcspn(token, " \t\r");
        return f;
    }

    static inline void parseFloat2(float& x, float& y, const char*& token) {
        x = parseFloat(token);
        y = parseFloat(token);
    }

    static inline void parseFloat3(float& x, float& y, float& z, const char*& token) {
        x = parseFloat(token);
        y = parseFloat(token);
        z = parseFloat(token);
    }


    // Parse triples: i, i/j/k, i//k, i/j

    static vertex_index parseTriple(const char* &token, int vsize, int vnsize, int vtsize) {
        vertex_index vi(-1);

        vi.v_idx = fixIndex(atoi(token), vsize);
        token += strcspn(token, "/ \t\r");
        if(token[0] != '/') {
            return vi;
        }
        token++;

        // i//k
        if(token[0] == '/') {
            token++;
            vi.vn_idx = fixIndex(atoi(token), vnsize);
            token += strcspn(token, "/ \t\r");
            return vi;
        }

        // i/j/k or i/j
        vi.vt_idx = fixIndex(atoi(token), vtsize);
        token += strcspn(token, "/ \t\r");
        if(token[0] != '/') {
            return vi;
        }

        // i/j/k
        token++; // skip '/'
        vi.vn_idx = fixIndex(atoi(token), vnsize);
        token += strcspn(token, "/ \t\r");
        return vi;
    }

    /**
     * SoA compatible version of updateVertex
     * @param vertexCache
     * @param positions
     * @param normals
     * @param texcoords
     * @param in_positions
     * @param in_normals
     * @param in_texcoords
     * @param i
     * @return 
     */
    static unsigned int updateVertex(std::map<vertex_index, unsigned int>& vertexCache,
                                     fg::CVector<float>& positions,
                                     fg::CVector<float>& normals,
                                     fg::CVector<float>& texcoords,
                                     const fg::CVector<float>& in_positions,
                                     const fg::CVector<float>& in_normals,
                                     const fg::CVector<float>& in_texcoords,
                                     const vertex_index& i) {
        const std::map<vertex_index, unsigned int>::iterator it = vertexCache.find(i);

        if(it != vertexCache.end()) {
            // found cache
            return it->second;
        }

        assert(in_positions.size() > (unsigned int)(3 * i.v_idx + 2));

        positions.push_back(in_positions[3 * i.v_idx + 0]);
        positions.push_back(in_positions[3 * i.v_idx + 1]);
        positions.push_back(in_positions[3 * i.v_idx + 2]);

        if(i.vn_idx >= 0) {
            normals.push_back(in_normals[3 * i.vn_idx + 0]);
            normals.push_back(in_normals[3 * i.vn_idx + 1]);
            normals.push_back(in_normals[3 * i.vn_idx + 2]);
        }

        if(i.vt_idx >= 0) {
            texcoords.push_back(in_texcoords[2 * i.vt_idx + 0]);
            texcoords.push_back(in_texcoords[2 * i.vt_idx + 1]);
        }

        unsigned int idx = positions.size() / 3 - 1;
        vertexCache[i] = idx;

        return idx;
    }

    /**
     * AoS compatible version of updateVertex
     * @param vertexCache
     * @param vertices
     * @param in_positions
     * @param in_normals
     * @param in_texcoords
     * @param i
     * @return 
     */
    static unsigned int updateVertex(std::map<vertex_index, unsigned int>& vertexCache,
                                     fg::CVector<fg::gfx::Vertex3v> & vertices,
                                     const fg::CVector<float>& in_positions,
                                     const fg::CVector<float>& in_normals,
                                     const fg::CVector<float>& in_texcoords,
                                     const vertex_index& i) {
        const std::map<vertex_index, unsigned int>::iterator it = vertexCache.find(i);

        if(it != vertexCache.end()) {
            // found cache
            return it->second;
        }

        assert(in_positions.size() > (unsigned int)(3 * i.v_idx + 2));
        fg::gfx::Vertex3v vertex;

        vertex.position[0] = (in_positions[3 * i.v_idx + 0]);
        vertex.position[1] = (in_positions[3 * i.v_idx + 1]);
        vertex.position[2] = (in_positions[3 * i.v_idx + 2]);

        if(i.vn_idx >= 0) {
            vertex.normal[0] = (in_normals[3 * i.vn_idx + 0]);
            vertex.normal[1] = (in_normals[3 * i.vn_idx + 1]);
            vertex.normal[2] = (in_normals[3 * i.vn_idx + 2]);
        }

        if(i.vt_idx >= 0) {
            vertex.uv[0] = (in_texcoords[2 * i.vt_idx + 0]);
            // FLIP TEXTURE
            vertex.uv[1] = (1.0f - in_texcoords[2 * i.vt_idx + 1]);
        }

        vertices.push_back(vertex);

        unsigned int idx = vertices.size() - 1;
        vertexCache[i] = idx;

        return idx;
    }

    /*
     * This is used for SoA/AoS (structure of arrays) shape/mesh mode
     * @param shape
     * @param in_positions
     * @param in_normals
     * @param in_texcoords
     * @param faceGroup
     * @param material
     * @param name
     * @param is_material_set
     * @param forceAoS
     * @return 
     */
    static fgBool exportFaceGroupToShape(fg::gfx::SShape *shape,
                                         const fg::CVector<float> &in_positions,
                                         const fg::CVector<float> &in_normals,
                                         const fg::CVector<float> &in_texcoords,
                                         const fg::CVector<fg::CVector<vertex_index> >& faceGroup,
                                         const fg::gfx::SMaterial &material,
                                         const std::string &name,
                                         const fgBool is_material_set,
                                         const fgBool forceAoS = FG_TRUE) {
        if(faceGroup.empty() || !shape) {
            return FG_FALSE;
        }

        // Flattened version of vertex data
        fg::CVector<float> positions;
        fg::CVector<float> normals;
        fg::CVector<float> texcoords;
        std::map<vertex_index, unsigned int> vertexCache;
        fg::CVector<fgGFXushort> indices; // unsigned short FIXME ! 
        fg::CVector<fg::gfx::Vertex3v> vertices;
        // Flatten vertices and indices
        for(size_t i = 0; i < faceGroup.size(); i++) {
            const fg::CVector<vertex_index>& face = faceGroup[i];

            vertex_index i0 = face[0];
            vertex_index i1(-1);
            vertex_index i2 = face[1];

            size_t npolys = face.size();

            // Polygon -> triangle fan conversion
            for(size_t k = 2; k < npolys; k++) {
                i1 = i2;
                i2 = face[k];

                unsigned int v0 = 0, v1 = 0, v2 = 0;

                if(forceAoS) {
                    v0 = updateVertex(vertexCache, vertices, in_positions, in_normals, in_texcoords, i0);
                    v1 = updateVertex(vertexCache, vertices, in_positions, in_normals, in_texcoords, i1);
                    v2 = updateVertex(vertexCache, vertices, in_positions, in_normals, in_texcoords, i2);
                } else {
                    v0 = updateVertex(vertexCache, positions, normals, texcoords, in_positions, in_normals, in_texcoords, i0);
                    v1 = updateVertex(vertexCache, positions, normals, texcoords, in_positions, in_normals, in_texcoords, i1);
                    v2 = updateVertex(vertexCache, positions, normals, texcoords, in_positions, in_normals, in_texcoords, i2);
                }

                indices.push_back(v0);
                indices.push_back(v1);
                indices.push_back(v2);
            }

        }

        //
        // Construct shape.
        //
        shape->name = name;
        if(forceAoS) {
            if(!shape->mesh) {
                shape->mesh = new fg::gfx::SMeshAoS();
            }
            FG_LOG_DEBUG("fgTinyObj: Constructing AoS mesh in shape: '%s'", shape->name.c_str());
            ((fg::gfx::SMeshAoS *)shape->mesh)->vertices.swap(vertices);
            ((fg::gfx::SMeshAoS *)shape->mesh)->indices.swap(indices);
        } else {
            if(!shape->mesh) {
                shape->mesh = new fg::gfx::SMeshSoA();
            }
            FG_LOG_DEBUG("fgTinyObj: Constructing SoA mesh in shape: '%s'", shape->name.c_str());
            ((fg::gfx::SMeshSoA *)shape->mesh)->vertices.swap(positions);
            ((fg::gfx::SMeshSoA *)shape->mesh)->normals.swap(normals);
            ((fg::gfx::SMeshSoA *)shape->mesh)->uvs.swap(texcoords);
            ((fg::gfx::SMeshSoA *)shape->mesh)->indices.swap(indices);
        }

        if(is_material_set) {
            if(!shape->material)
                shape->material = new fg::gfx::SMaterial(material);
            /*else
            shape.material(material);*/
        } else {
            if(!shape->material)
                shape->material = new fg::gfx::SMaterial();
            InitMaterial(*shape->material);
            shape->material->diffuse[0] = 1.f;
            shape->material->diffuse[1] = 1.f;
            shape->material->diffuse[2] = 1.f;
        }

        return FG_TRUE;
    }

    std::string LoadMtlIni(std::map<std::string, fg::gfx::SMaterial>& material_map, const std::string& path) {
        material_map.clear();
        std::stringstream err;
        fg::gfx::SMaterial material;

        fg::util::CConfig m_config;
        if(!m_config.load(path.c_str())) {
            return err.str();
        }

        fg::util::SCfgSection *section = m_config.getSection("Material");
        if(!section) {
            FG_LOG_ERROR("fgTinyObj: Couldn't find 'Material' section in: '%s'", path.c_str());
            return err.str();
        }

        fg::util::config::ParameterVecItor end, itor;
        end = section->parameters.end();
        itor = section->parameters.begin();
        for(; itor != end; itor++) {
            fg::util::SCfgParameter *param = *itor;
            if(!param)
                continue;
            if(param->name.compare("name") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.name = param->string;
                }

            } else if(param->name.compare("ambient") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.ambient = fgStringParser::parseColor(param->string);
                }

            } else if(param->name.compare("diffuse") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.diffuse = fgStringParser::parseColor(param->string);
                }

            } else if(param->name.compare("specular") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.specular = fgStringParser::parseColor(param->string);
                }

            } else if(param->name.compare("transmittance") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.transmittance = fgStringParser::parseColor(param->string);
                }

            } else if(param->name.compare("emission") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.emission = fgStringParser::parseColor(param->string);
                }

            } else if(param->name.compare("shininess") == 0) {
                if(param->type == fg::util::SCfgParameter::FLOAT) {
                    material.shininess = param->float_val;
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.shininess = (float)param->int_val;
                }

            } else if(param->name.compare("ior") == 0) {
                if(param->type == fg::util::SCfgParameter::FLOAT) {
                    material.ior = param->float_val;
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.ior = (float)param->int_val;
                }

            } else if(param->name.compare("dissolve") == 0) {
                if(param->type == fg::util::SCfgParameter::FLOAT) {
                    material.dissolve = param->float_val;
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.dissolve = (float)param->int_val;
                }

            } else if(param->name.compare("illumination-model") == 0 || param->name.compare("illum-model") == 0) {
                if(param->type == fg::util::SCfgParameter::INT) {
                    material.illuminationModel = param->int_val;
                }

            } else if(param->name.compare("burn") == 0) {
                if(param->type == fg::util::SCfgParameter::FLOAT) {
                    material.burn = param->float_val;
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.burn = (float)param->int_val;
                }

            } else if(param->name.compare("ambient-map") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.ambientTexName = param->string;
                }

            } else if(param->name.compare("diffuse-map") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.diffuseTexName = param->string;
                }

            } else if(param->name.compare("specular-map") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.specularTexName = param->string;
                }

            } else if(param->name.compare("normal-map") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.normalTexName = param->string;
                }

            } else if(param->name.compare("shader-name") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    material.shaderName = param->string;
                }

            } else if(param->name.compare("blend-mode") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    // case insensitive
                    if(fg::strings::isEqual(param->string, "additive", FG_FALSE)) {
                        material.blendMode = fg::gfx::BlendMode::BLEND_ADDITIVE;
                    } else if(fg::strings::isEqual(param->string, "transparency", FG_FALSE)) {
                        material.blendMode = fg::gfx::BlendMode::BLEND_TRANSPARENCY;
                    }
                }

            } else if(param->name.compare("front-face") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    if(fg::strings::isEqual(param->string, "ccw", FG_FALSE)) {
                        material.setFrontFace(fg::gfx::FACE_CCW);
                    } else if(fg::strings::isEqual(param->string, "cw", FG_FALSE)) {
                        material.setFrontFace(fg::gfx::FACE_CW);
                    }
                }

            } else if(param->name.compare("cull-face") == 0) {
                if(param->type == fg::util::SCfgParameter::BOOL) {
                    material.setCullFace(param->bool_val);
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.setCullFace((fgBool)param->int_val);
                }

            } else if(param->name.compare("depth-test") == 0) {
                if(param->type == fg::util::SCfgParameter::BOOL) {
                    material.setDepthTest(param->bool_val);
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.setDepthTest((fgBool)param->int_val);
                }
                
            } else if(param->name.compare("depth-write-mask") == 0) {
                if(param->type == fg::util::SCfgParameter::BOOL) {
                    material.setDepthWriteMask(param->bool_val);
                } else if(param->type == fg::util::SCfgParameter::INT) {
                    material.setDepthWriteMask((fgBool)param->int_val);
                }
                
            } else if(param->name.compare("mtl-reference") == 0) {
                if(param->type == fg::util::SCfgParameter::STRING) {
                    // ????
                }
            }
        }

        m_config.clearAll();
        
        // flush last material.
        material_map.insert(std::pair<std::string, fg::gfx::SMaterial>(material.name, material));
        return err.str();
    }

    /**
     * 
     * @param material_map
     * @param inStream
     * @return 
     */
    std::string LoadMtl(std::map<std::string, fg::gfx::SMaterial>& material_map, std::istream& inStream) {
        material_map.clear();
        std::stringstream err;
        fg::gfx::SMaterial material;

        int maxchars = 8192; // Alloc enough size.
        fg::CVector<char> buf; // Alloc enough size.
        buf.reserve(maxchars);
        while(inStream.peek() != -1) {
            inStream.getline(&buf[0], maxchars);

            std::string linebuf(&buf[0]);

            // Trim newline '\r\n' or '\n'
            if(linebuf.size() > 0) {
                if(linebuf[linebuf.size() - 1] == '\n') linebuf.erase(linebuf.size() - 1);
            }
            if(linebuf.size() > 0) {
                if(linebuf[linebuf.size() - 1] == '\r') linebuf.erase(linebuf.size() - 1);
            }

            // Skip if empty line.
            if(linebuf.empty()) {
                continue;
            }

            // Skip leading space.
            const char* token = linebuf.c_str();
            token += strspn(token, " \t");

            assert(token);
            if(token[0] == '\0') continue; // empty line

            if(token[0] == '#') continue; // comment line

            // new mtl
            if((0 == strncmp(token, "newmtl", 6)) && isSpace((token[6]))) {
                // flush previous material.
                material_map.insert(std::pair<std::string, fg::gfx::SMaterial>(material.name, material));

                // initial temporary material
                InitMaterial(material);

                // set new mtl name
                char namebuf[4096];
                token += 7;
                sscanf(token, "%s", namebuf);
                material.name = namebuf;
                continue;
            }

            // ambient
            if(token[0] == 'K' && token[1] == 'a' && isSpace((token[2]))) {
                token += 2;
                float r, g, b;
                parseFloat3(r, g, b, token);
                material.ambient[0] = r;
                material.ambient[1] = g;
                material.ambient[2] = b;
                continue;
            }

            // diffuse
            if(token[0] == 'K' && token[1] == 'd' && isSpace((token[2]))) {
                token += 2;
                float r, g, b;
                parseFloat3(r, g, b, token);
                material.diffuse[0] = r;
                material.diffuse[1] = g;
                material.diffuse[2] = b;
                continue;
            }

            // specular
            if(token[0] == 'K' && token[1] == 's' && isSpace((token[2]))) {
                token += 2;
                float r, g, b;
                parseFloat3(r, g, b, token);
                material.specular[0] = r;
                material.specular[1] = g;
                material.specular[2] = b;
                continue;
            }

            // transmittance - transmission filter 
            if(token[0] == 'T' && token[1] == 'f' && isSpace((token[2]))) {
                token += 2;
                float r, g, b;
                parseFloat3(r, g, b, token);
                material.transmittance[0] = r;
                material.transmittance[1] = g;
                material.transmittance[2] = b;
                continue;
            }

            // ior(index of refraction)
            if(token[0] == 'N' && token[1] == 'i' && isSpace((token[2]))) {
                token += 2;
                material.ior = parseFloat(token);
                continue;
            }

            // emission
            if(token[0] == 'K' && token[1] == 'e' && isSpace(token[2])) {
                token += 2;
                float r, g, b;
                parseFloat3(r, g, b, token);
                material.emission[0] = r;
                material.emission[1] = g;
                material.emission[2] = b;
                continue;
            }

            // shininess - specular exponent - defines the focus of the specular highlight - 0 - 1000
            if(token[0] == 'N' && token[1] == 's' && isSpace(token[2])) {
                token += 2;
                material.shininess = parseFloat(token);
                continue;
            }

            // illum model
            if(0 == strncmp(token, "illum", 5) && isSpace(token[5])) {
                token += 6;
                material.illuminationModel = parseInt(token);
                continue;
            }

            // dissolve
            if((token[0] == 'd' && isSpace(token[1]))) {
                token += 1;
                material.dissolve = parseFloat(token);
                continue;
            }
            if(token[0] == 'T' && token[1] == 'r' && isSpace(token[2])) {
                token += 2;
                material.dissolve = parseFloat(token);
                continue;
            }

            // ambient texture
            if((0 == strncmp(token, "map_Ka", 6)) && isSpace(token[6])) {
                token += 7;
                material.ambientTexName = token;
                continue;
            }

            // diffuse texture
            if((0 == strncmp(token, "map_Kd", 6)) && isSpace(token[6])) {
                token += 7;
                material.diffuseTexName = token;
                continue;
            }

            // specular texture
            if((0 == strncmp(token, "map_Ks", 6)) && isSpace(token[6])) {
                token += 7;
                material.specularTexName = token;
                continue;
            }

            // normal texture
            if((0 == strncmp(token, "map_Ns", 6)) && isSpace(token[6])) {
                token += 7;
                material.normalTexName = token;
                continue;
            }

            // unknown parameter
            const char* _space = strchr(token, ' ');
            if(!_space) {
                _space = strchr(token, '\t');
            }
            if(_space) {
                int len = _space - token;
                std::string key(token, len);
                std::string value = _space + 1;
                material.unknownParam.insert(std::pair<std::string, std::string>(key, value));
            }
        }
        // flush last material.
        material_map.insert(std::pair<std::string, fg::gfx::SMaterial>(material.name, material));

        return err.str();
    }

    /**
     * 
     * @param matId
     * @param matMap
     * @return 
     */
    std::string MaterialFileReader::operator ()(const std::string& matId,
                                                std::map<std::string, fg::gfx::SMaterial>& matMap) {
        std::string filepath;

        if(!m_mtlBasePath.empty()) {
            filepath = std::string(m_mtlBasePath) + matId;
        } else {
            filepath = matId;
        }

        const char *ext = fg::path::fileExt(filepath.c_str(), FG_TRUE);
        if(fg::strings::endsWith(ext, "mtl")) {
            std::ifstream matIStream(filepath.c_str());
            return LoadMtl(matMap, matIStream);
        } else if(fg::strings::endsWith(ext, "mat.ini")) {
            return LoadMtlIni(matMap, filepath);
        }

        return std::string();
    }

    /**
     * 
     * @param shapes
     * @param filename
     * @param mtl_basepath
     * @param forceAoS
     * @return 
     */
    std::string LoadObj(fg::CVector<fg::gfx::SShape *>& shapes,
                        const char* filename,
                        const char* mtl_basepath,
                        fgBool forceAoS) {
        shapes.clear();
        std::stringstream err;

        std::ifstream ifs(filename);
        if(!ifs) {
            err << "Cannot open file [" << filename << "]" << std::endl;
            return err.str();
        }

        std::string basePath;
        if(mtl_basepath) {
            basePath = mtl_basepath;
        }
        MaterialFileReader matFileReader(basePath);

        return LoadObj(shapes, ifs, matFileReader, forceAoS);
    }

    /**
     * 
     * @param shapes
     * @param inStream
     * @param readMatFn
     * @param forceAoS
     * @return 
     */
    std::string LoadObj(fg::CVector<fg::gfx::SShape *>& shapes,
                        std::istream& inStream,
                        MaterialReader& readMatFn,
                        fgBool forceAoS) {
        std::stringstream err;
        float t1 = fg::timesys::ms();

        fg::CVector<float> v;
        fg::CVector<float> vn;
        fg::CVector<float> vt;
        fg::CVector<fg::CVector<vertex_index> > faceGroup;
        std::string name;

        // material
        std::map<std::string, fg::gfx::SMaterial> material_map;
        fg::gfx::SMaterial material;
        bool is_material_seted = false;

        int maxchars = 8192; // Alloc enough size.
        fg::CVector<char> buf; // Alloc enough size.
        buf.resize(maxchars);
        float l1 = fg::timesys::ms();
        while(inStream.peek() != -1) {
            inStream.getline(&buf[0], maxchars);

            std::string linebuf(&buf[0]);

            // Trim newline '\r\n' or '\n'
            if(linebuf.size() > 0) {
                if(linebuf[linebuf.size() - 1] == '\n') linebuf.erase(linebuf.size() - 1);
            }
            if(linebuf.size() > 0) {
                if(linebuf[linebuf.size() - 1] == '\r') linebuf.erase(linebuf.size() - 1);
            }

            // Skip if empty line.
            if(linebuf.empty()) {
                continue;
            }

            // Skip leading space.
            const char* token = linebuf.c_str();
            token += strspn(token, " \t");

            assert(token);
            if(token[0] == '\0') continue; // empty line
            if(token[0] == '#') continue; // comment line

            // vertex
            if(token[0] == 'v' && isSpace((token[1]))) {
                token += 2;
                float x, y, z;
                parseFloat3(x, y, z, token);
                v.push_back(x);
                v.push_back(y);
                v.push_back(z);
                continue;
            }

            // normal
            if(token[0] == 'v' && token[1] == 'n' && isSpace((token[2]))) {
                token += 3;
                float x, y, z;
                parseFloat3(x, y, z, token);
                vn.push_back(x);
                vn.push_back(y);
                vn.push_back(z);
                continue;
            }

            // texcoord
            if(token[0] == 'v' && token[1] == 't' && isSpace((token[2]))) {
                token += 3;
                float x, y;
                parseFloat2(x, y, token);
                vt.push_back(x);
                vt.push_back(y);
                continue;
            }

            // face
            if(token[0] == 'f' && isSpace((token[1]))) {
                token += 2;
                token += strspn(token, " \t");

                fg::CVector<vertex_index> face;
                while(!isNewLine(token[0])) {
                    vertex_index vi = parseTriple(token, v.size() / 3, vn.size() / 3, vt.size() / 2);
                    face.push_back(vi);
                    int n = strspn(token, " \t\r");
                    token += n;
                }

                faceGroup.push_back(face);

                continue;
            }

            // use mtl
            if((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6]))) {

                char namebuf[4096];
                token += 7;
                sscanf(token, "%s", namebuf);

                if(material_map.find(namebuf) != material_map.end()) {
                    material = material_map[namebuf];
                    is_material_seted = FG_TRUE;
                } else {
                    // { error!! material not found }
                    InitMaterial(material);
                }
                continue;

            }

            // load mtl
            if((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6]))) {
                char namebuf[4096];
                token += 7;
                sscanf(token, "%s", namebuf);

                std::string err_mtl = readMatFn(namebuf, material_map);
                if(!err_mtl.empty()) {
                    faceGroup.clear(); // for safety
                    return err_mtl;
                }

                continue;
            }

            // group name
            if(token[0] == 'g' && isSpace((token[1]))) {

                // flush previous face group.
                fg::gfx::SShape *shape = new fg::gfx::SShape();
                fgBool ret = exportFaceGroupToShape(shape, v, vn, vt, faceGroup, material, name, is_material_seted, forceAoS);
                if(ret) {
                    shapes.push_back(shape);
                } else {
                    delete shape;
                }

                is_material_seted = false;
                faceGroup.clear();

                fg::CStringVector names;
                while(!isNewLine(token[0])) {
                    std::string str = parseString(token);
                    names.push_back(str);
                    token += strspn(token, " \t\r"); // skip tag
                }

                assert(names.size() > 0);

                // names[0] must be 'g', so skipt 0th element.
                if(names.size() > 1) {
                    name = names[1];
                } else {
                    name = "";
                }

                continue;
            }

            // object name
            if(token[0] == 'o' && isSpace((token[1]))) {

                // flush previous face group.
                fg::gfx::SShape *shape = new fg::gfx::SShape();
                fgBool ret = exportFaceGroupToShape(shape, v, vn, vt, faceGroup, material, name, is_material_seted, forceAoS);
                if(ret) {
                    shapes.push_back(shape);
                } else {
                    delete shape;
                }

                is_material_seted = FG_FALSE;
                faceGroup.clear();

                // @todo { multiple object name? }
                char namebuf[4096];
                token += 2;
                sscanf(token, "%s", namebuf);
                name = std::string(namebuf);

                continue;
            }
            // Ignore unknown command.
        } // while (inStream.peek() != -1)
        float l2 = fg::timesys::ms();
        FG_LOG_DEBUG("fgTinyObj: load raw data: %.2f seconds", (l2 - l1) / 1000.0f);

        fg::gfx::SShape *shape = new fg::gfx::SShape();
        float e1 = fg::timesys::ms();
        fgBool ret = exportFaceGroupToShape(shape, v, vn, vt, faceGroup, material, name, is_material_seted, forceAoS);
        float e2 = fg::timesys::ms();
        FG_LOG_DEBUG("fgTinyObj: exportFaceGroupToShape: %.2f seconds", (e2 - e1) / 1000.0f);
        if(ret) {
            shapes.push_back(shape);
        }
        is_material_seted = FG_FALSE; // for safety
        faceGroup.clear(); // for safety
        float t2 = fg::timesys::ms();
        FG_LOG_DEBUG("fgTinyObj: total %.2f seconds", (t2 - t1) / 1000.0f);

        return err.str();
    }

};
