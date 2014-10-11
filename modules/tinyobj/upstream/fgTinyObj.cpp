//
// Copyright 2012-2013, Syoyo Fujita.
// 
// Licensed under 2-clause BSD liecense.
//

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


#include <cstdlib>
#include <cstring>
#include <cassert>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "fgTinyObj.h"

namespace fgTinyObj {

void InitMaterial(fgGfxMaterial& material) {
	material.name = "";
	material.ambientTexName = "";
	material.diffuseTexName = "";
	material.specularTexName = "";
	material.normalTexName = "";
	for (int i = 0; i < 3; i ++) {
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

struct vertex_index {
	int v_idx, vt_idx, vn_idx;
	vertex_index() {};
	vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx) {};
	vertex_index(int vidx, int vtidx, int vnidx) : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx) {};

};

// for std::map
static inline bool operator<(const vertex_index& a, const vertex_index& b)
{
	if (a.v_idx != b.v_idx) return (a.v_idx < b.v_idx);
	if (a.vn_idx != b.vn_idx) return (a.vn_idx < b.vn_idx);
	if (a.vt_idx != b.vt_idx) return (a.vt_idx < b.vt_idx);

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
static inline int fixIndex(int idx, int n)
{
	int i;

	if (idx > 0) {
		i = idx - 1;
	} else if (idx == 0) {
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
static vertex_index parseTriple(const char* &token, int vsize, int vnsize, int vtsize)
{
    vertex_index vi(-1);

    vi.v_idx = fixIndex(atoi(token), vsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
      return vi;
    }
    token++;

    // i//k
    if (token[0] == '/') {
      token++;
      vi.vn_idx = fixIndex(atoi(token), vnsize);
      token += strcspn(token, "/ \t\r");
      return vi;
    }
    
    // i/j/k or i/j
    vi.vt_idx = fixIndex(atoi(token), vtsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
      return vi;
    }

    // i/j/k
    token++;  // skip '/'
    vi.vn_idx = fixIndex(atoi(token), vnsize);
    token += strcspn(token, "/ \t\r");
    return vi; 
}

static unsigned int updateVertex(
	std::map<vertex_index, unsigned int>& vertexCache,
	fgVector<float>& positions,
	fgVector<float>& normals,
	fgVector<float>& texcoords,
	const fgVector<float>& in_positions,
	const fgVector<float>& in_normals,
	const fgVector<float>& in_texcoords,
	const vertex_index& i)
{
	const std::map<vertex_index, unsigned int>::iterator it = vertexCache.find(i);

	if (it != vertexCache.end()) {
		// found cache
		return it->second;
	}

	assert(in_positions.size() > (unsigned int) (3*i.v_idx+2));

	positions.push_back(in_positions[3*i.v_idx+0]);
	positions.push_back(in_positions[3*i.v_idx+1]);
	positions.push_back(in_positions[3*i.v_idx+2]);

	if (i.vn_idx >= 0) {
		normals.push_back(in_normals[3*i.vn_idx+0]);
		normals.push_back(in_normals[3*i.vn_idx+1]);
		normals.push_back(in_normals[3*i.vn_idx+2]);
	}

	if (i.vt_idx >= 0) {
		texcoords.push_back(in_texcoords[2*i.vt_idx+0]);
		texcoords.push_back(in_texcoords[2*i.vt_idx+1]);
	}

	unsigned int idx = positions.size() / 3 - 1;
	vertexCache[i] = idx;

	return idx;
}

/*
 * AoS compatible version of updateVertex
 */ 
static unsigned int updateVertex(
	std::map<vertex_index, unsigned int>& vertexCache,
	fgVector<fgVertex3> & vertices,
	const fgVector<float>& in_positions,
	const fgVector<float>& in_normals,
	const fgVector<float>& in_texcoords,
	const vertex_index& i)
{
	const std::map<vertex_index, unsigned int>::iterator it = vertexCache.find(i);

	if (it != vertexCache.end()) {
		// found cache
		return it->second;
	}

	assert(in_positions.size() > (unsigned int) (3*i.v_idx+2));
	fgVertex3 vertex;

	vertex.position[0] = (in_positions[3*i.v_idx+0]);
	vertex.position[1] = (in_positions[3*i.v_idx+1]);
	vertex.position[2] = (in_positions[3*i.v_idx+2]);

	if (i.vn_idx >= 0) {
		vertex.normal[0] = (in_normals[3*i.vn_idx+0]);
		vertex.normal[1] = (in_normals[3*i.vn_idx+1]);
		vertex.normal[2] = (in_normals[3*i.vn_idx+2]);
	}

	if (i.vt_idx >= 0) {
		vertex.uv[0] = (in_texcoords[2*i.vt_idx+0]);
		// FLIP TEXTURE
		vertex.uv[1] = (1.0f-in_texcoords[2*i.vt_idx+1]);
	}

	vertices.push_back(vertex);

	unsigned int idx = vertices.size() - 1;
	vertexCache[i] = idx;

	return idx;
}

/*
 * This is used for SoA (structure of arrays) shape/mesh mode
 */
static fgBool exportFaceGroupToShape(fgGfxShape *shape,
  const fgVector<float> &in_positions,
  const fgVector<float> &in_normals,
  const fgVector<float> &in_texcoords,
  const fgVector<fgVector<vertex_index> >& faceGroup,
  const fgGfxMaterial &material,
  const std::string &name,
  const fgBool is_material_seted,
  const fgBool forceAoS = FG_TRUE)
{
	if (faceGroup.empty() || !shape) {
		return FG_FALSE;
	}

	// Flattened version of vertex data
	fgVector<float> positions;
	fgVector<float> normals;
	fgVector<float> texcoords;
	std::map<vertex_index, unsigned int> vertexCache;
	fgVector<fgGFXushort> indices; // unsigned short FIXME ! 
	fgVector<fgVertex3> vertices;
	// Flatten vertices and indices
	for (size_t i = 0; i < faceGroup.size(); i++) {
		const fgVector<vertex_index>& face = faceGroup[i];

		vertex_index i0 = face[0];
		vertex_index i1(-1);
		vertex_index i2 = face[1];

		size_t npolys = face.size();

		// Polygon -> triangle fan conversion
		for (size_t k = 2; k < npolys; k++) {
			i1 = i2;
			i2 = face[k];

			unsigned int v0=0,v1=0,v2=0;

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
			shape->mesh = new fgGfxMeshAoS();
		}
		FG_LOG::PrintDebug("fgTinyObj: Constructing AoS mesh in shape: '%s'", shape->name.c_str());
		((fgGfxMeshAoS *)shape->mesh)->vertices.swap(vertices);
		((fgGfxMeshAoS *)shape->mesh)->indices.swap(indices);
	} else {
		if(!shape->mesh) {
			shape->mesh = new fgGfxMeshSoA();
		}
		FG_LOG::PrintDebug("fgTinyObj: Constructing SoA mesh in shape: '%s'", shape->name.c_str());
		((fgGfxMeshSoA *)shape->mesh)->vertices.swap(positions);
		((fgGfxMeshSoA *)shape->mesh)->normals.swap(normals);
		((fgGfxMeshSoA *)shape->mesh)->uvs.swap(texcoords);
		((fgGfxMeshSoA *)shape->mesh)->indices.swap(indices);
	}

	if(is_material_seted) {
		if(!shape->material)
			shape->material = new fgGfxMaterial(material);
		/*else
		shape.material(material);*/
	} else {
		if(!shape->material)
			shape->material = new fgGfxMaterial();
		InitMaterial(*shape->material);
		shape->material->diffuse[0] = 1.f;
		shape->material->diffuse[1] = 1.f;
		shape->material->diffuse[2] = 1.f;
	}

	return FG_TRUE;
}

/*
 *
 */
std::string LoadMtl(std::map<std::string, fgGfxMaterial>& material_map, std::istream& inStream)
{
	material_map.clear();
	std::stringstream err;
	fgGfxMaterial material;

	int maxchars = 8192;  // Alloc enough size.
	std::vector<char> buf(maxchars);  // Alloc enough size.
	while (inStream.peek() != -1) {
		inStream.getline(&buf[0], maxchars);

		std::string linebuf(&buf[0]);

		// Trim newline '\r\n' or '\n'
		if (linebuf.size() > 0) {
			if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
		}
		if (linebuf.size() > 0) {
			if (linebuf[linebuf.size()-1] == '\r') linebuf.erase(linebuf.size()-1);
		}

		// Skip if empty line.
		if (linebuf.empty()) {
			continue;
		}

		// Skip leading space.
		const char* token = linebuf.c_str();
		token += strspn(token, " \t");

		assert(token);
		if (token[0] == '\0') continue; // empty line

		if (token[0] == '#') continue;  // comment line

		// new mtl
		if ((0 == strncmp(token, "newmtl", 6)) && isSpace((token[6]))) {
			// flush previous material.
			material_map.insert(std::pair<std::string, fgGfxMaterial>(material.name, material));

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
		if (token[0] == 'K' && token[1] == 'a' && isSpace((token[2]))) {
			token += 2;
			float r, g, b;
			parseFloat3(r, g, b, token);
			material.ambient[0] = r;
			material.ambient[1] = g;
			material.ambient[2] = b;
			continue;
		}

		// diffuse
		if (token[0] == 'K' && token[1] == 'd' && isSpace((token[2]))) {
			token += 2;
			float r, g, b;
			parseFloat3(r, g, b, token);
			material.diffuse[0] = r;
			material.diffuse[1] = g;
			material.diffuse[2] = b;
			continue;
		}

		// specular
		if (token[0] == 'K' && token[1] == 's' && isSpace((token[2]))) {
			token += 2;
			float r, g, b;
			parseFloat3(r, g, b, token);
			material.specular[0] = r;
			material.specular[1] = g;
			material.specular[2] = b;
			continue;
		}

		// transmittance
		if (token[0] == 'K' && token[1] == 't' && isSpace((token[2]))) {
			token += 2;
			float r, g, b;
			parseFloat3(r, g, b, token);
			material.transmittance[0] = r;
			material.transmittance[1] = g;
			material.transmittance[2] = b;
			continue;
		}

		// ior(index of refraction)
		if (token[0] == 'N' && token[1] == 'i' && isSpace((token[2]))) {
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

		// shininess
		if(token[0] == 'N' && token[1] == 's' && isSpace(token[2])) {
			token += 2;
			material.shininess = parseFloat(token);
			continue;
		}

		// illum model
		if (0 == strncmp(token, "illum", 5) && isSpace(token[5])) {
			token += 6;
			material.illuminationModel = parseInt(token);
			continue;
		}

		// dissolve
		if ((token[0] == 'd' && isSpace(token[1]))) {
			token += 1;
			material.dissolve = parseFloat(token);
			continue;
		}
		if (token[0] == 'T' && token[1] == 'r' && isSpace(token[2])) {
			token += 2;
			material.dissolve = parseFloat(token);
			continue;
		}

		// ambient texture
		if ((0 == strncmp(token, "map_Ka", 6)) && isSpace(token[6])) {
			token += 7;
			material.ambientTexName = token;
			continue;
		}

		// diffuse texture
		if ((0 == strncmp(token, "map_Kd", 6)) && isSpace(token[6])) {
			token += 7;
			material.diffuseTexName = token;
			continue;
		}

		// specular texture
		if ((0 == strncmp(token, "map_Ks", 6)) && isSpace(token[6])) {
			token += 7;
			material.specularTexName = token;
			continue;
		}

		// normal texture
		if ((0 == strncmp(token, "map_Ns", 6)) && isSpace(token[6])) {
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
	material_map.insert(std::pair<std::string, fgGfxMaterial>(material.name, material));

	return err.str();
}

std::string MaterialFileReader::operator() (
	const std::string& matId,
	std::map<std::string, fgGfxMaterial>& matMap)
{
	std::string filepath;

	if (!m_mtlBasePath.empty()) {
		filepath = std::string(m_mtlBasePath) + matId;
	} else {
		filepath = matId;
	}

	std::ifstream matIStream(filepath.c_str());
	return LoadMtl(matMap, matIStream);
}

std::string LoadObj(fgVector<fgGfxShape *>& shapes,
					const char* filename,
					const char* mtl_basepath,
					fgBool forceAoS)
{
	shapes.clear();
	std::stringstream err;

	std::ifstream ifs(filename);
	if (!ifs) {
		err << "Cannot open file [" << filename << "]" << std::endl;
		return err.str();
	}

	std::string basePath;
	if (mtl_basepath) {
		basePath = mtl_basepath;
	}
	MaterialFileReader matFileReader( basePath );

	return LoadObj(shapes, ifs, matFileReader, forceAoS);
}


std::string LoadObj(fgVector<fgGfxShape *>& shapes,
					std::istream& inStream,
					MaterialReader& readMatFn,
					fgBool forceAoS)
{
	std::stringstream err;
	float t1 = fgTime::ms();

	fgVector<float> v;
	fgVector<float> vn;
	fgVector<float> vt;
	fgVector<fgVector<vertex_index> > faceGroup;
	std::string name;

	// material
	std::map<std::string, fgGfxMaterial> material_map;
	fgGfxMaterial material;
	bool is_material_seted = false;

	int maxchars = 8192;  // Alloc enough size.
	fgVector<char> buf;  // Alloc enough size.
	buf.resize(maxchars);
	float l1 = fgTime::ms();
	while (inStream.peek() != -1) {
		inStream.getline(&buf[0], maxchars);

		std::string linebuf(&buf[0]);

		// Trim newline '\r\n' or '\n'
		if (linebuf.size() > 0) {
			if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
		}
		if (linebuf.size() > 0) {
			if (linebuf[linebuf.size()-1] == '\r') linebuf.erase(linebuf.size()-1);
		}

		// Skip if empty line.
		if (linebuf.empty()) {
			continue;
		}

		// Skip leading space.
		const char* token = linebuf.c_str();
		token += strspn(token, " \t");

		assert(token);
		if (token[0] == '\0') continue; // empty line
		if (token[0] == '#') continue;  // comment line

		// vertex
		if (token[0] == 'v' && isSpace((token[1]))) {
			token += 2;
			float x, y, z;
			parseFloat3(x, y, z, token);
			v.push_back(x);
			v.push_back(y);
			v.push_back(z);
			continue;
		}

		// normal
		if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2]))) {
			token += 3;
			float x, y, z;
			parseFloat3(x, y, z, token);
			vn.push_back(x);
			vn.push_back(y);
			vn.push_back(z);
			continue;
		}

		// texcoord
		if (token[0] == 'v' && token[1] == 't' && isSpace((token[2]))) {
			token += 3;
			float x, y;
			parseFloat2(x, y, token);
			vt.push_back(x);
			vt.push_back(y);
			continue;
		}

		// face
		if (token[0] == 'f' && isSpace((token[1]))) {
			token += 2;
			token += strspn(token, " \t");

			fgVector<vertex_index> face;
			while (!isNewLine(token[0])) {
				vertex_index vi = parseTriple(token, v.size() / 3, vn.size() / 3, vt.size() / 2);
				face.push_back(vi);
				int n = strspn(token, " \t\r");
				token += n;
			}

			faceGroup.push_back(face);

			continue;
		}

		// use mtl
		if ((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6]))) {

			char namebuf[4096];
			token += 7;
			sscanf(token, "%s", namebuf);

			if (material_map.find(namebuf) != material_map.end()) {
				material = material_map[namebuf];
				is_material_seted = FG_TRUE;
			} else {
				// { error!! material not found }
				InitMaterial(material);
			}
			continue;

		}

		// load mtl
		if ((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6]))) {
			char namebuf[4096];
			token += 7;
			sscanf(token, "%s", namebuf);

			std::string err_mtl = readMatFn(namebuf, material_map);
			if (!err_mtl.empty()) {
				faceGroup.clear();  // for safety
				return err_mtl;
			}

			continue;
		}

		// group name
		if (token[0] == 'g' && isSpace((token[1]))) {

			// flush previous face group.
			fgGfxShape *shape = new fgGfxShape();
			fgBool ret = exportFaceGroupToShape(shape, v, vn, vt, faceGroup, material, name, is_material_seted, forceAoS);
			if (ret) {
				shapes.push_back(shape);
			} else {
				delete shape;
			}

			is_material_seted = false;
			faceGroup.clear();

			fgStringVector names;
			while (!isNewLine(token[0])) {
				std::string str = parseString(token);
				names.push_back(str);
				token += strspn(token, " \t\r"); // skip tag
			}

			assert(names.size() > 0);

			// names[0] must be 'g', so skipt 0th element.
			if (names.size() > 1) {
				name = names[1];
			} else {
				name = "";
			}

			continue;
		}

		// object name
		if (token[0] == 'o' && isSpace((token[1]))) {

			// flush previous face group.
			fgGfxShape *shape = new fgGfxShape();
			fgBool ret = exportFaceGroupToShape(shape, v, vn, vt, faceGroup, material, name, is_material_seted, forceAoS);
			if (ret) {
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
	float l2 = fgTime::ms();
	FG_LOG::PrintDebug("fgTinyObj: load raw data: %.2f seconds", (l2-l1)/1000.0f);

	fgGfxShape *shape = new fgGfxShape();
	float e1 = fgTime::ms();
	fgBool ret = exportFaceGroupToShape(shape, v, vn, vt, faceGroup, material, name, is_material_seted, forceAoS);
	float e2 = fgTime::ms();
	FG_LOG::PrintDebug("fgTinyObj: exportFaceGroupToShape: %.2f seconds", (e2-e1)/1000.0f);
	if (ret) {
		shapes.push_back(shape);
	}
	is_material_seted = FG_FALSE; // for safety
	faceGroup.clear();  // for safety
	float t2 = fgTime::ms();
	FG_LOG::PrintDebug("fgTinyObj: total %.2f seconds", (t2-t1)/1000.0f);

	return err.str();
}

};
