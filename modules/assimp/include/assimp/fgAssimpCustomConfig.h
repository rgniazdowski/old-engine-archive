#ifndef FG_INC_ASSIMP_CUSTOM_CONFIG
#define FG_INC_ASSIMP_CUSTOM_CONFIG

#undef ASSIMP_DOXYGEN_BUILD
// use external zlib
// FlexiGame uses it's own internal zlib library with minizip compiled
#ifndef ASSIMP_BUILD_NO_OWN_ZLIB
#define ASSIMP_BUILD_NO_OWN_ZLIB
#endif

// Force to not use Boost as it is too heavy dependency
#ifndef ASSIMP_BUILD_BOOST_WORKAROUND
#define ASSIMP_BUILD_BOOST_WORKAROUND
#endif

#define ASSIMP_BUILD_NO_COMPRESSED_X
#define ASSIMP_BUILD_NO_COMPRESSED_IFC
#define ASSIMP_BUILD_NO_MD3_IMPORTER
#define ASSIMP_BUILD_NO_MDL_IMPORTER 
#define ASSIMP_BUILD_NO_MD2_IMPORTER
#define ASSIMP_BUILD_NO_PLY_IMPORTER
#define ASSIMP_BUILD_NO_ASE_IMPORTER
#define ASSIMP_BUILD_NO_HMP_IMPORTER 
#define ASSIMP_BUILD_NO_SMD_IMPORTER
#define ASSIMP_BUILD_NO_MDC_IMPORTER
#define ASSIMP_BUILD_NO_MD5_IMPORTER
#define ASSIMP_BUILD_NO_STL_IMPORTER
#define ASSIMP_BUILD_NO_NFF_IMPORTER
#define ASSIMP_BUILD_NO_RAW_IMPORTER
#define ASSIMP_BUILD_NO_AC_IMPORTER
#define ASSIMP_BUILD_NO_IRRMESH_IMPORTER
#define ASSIMP_BUILD_NO_IRR_IMPORTER
#define ASSIMP_BUILD_NO_Q3D_IMPORTER
#define ASSIMP_BUILD_NO_B3D_IMPORTER 
#define ASSIMP_BUILD_NO_TERRAGEN_IMPORTER 
#define ASSIMP_BUILD_NO_3D_IMPORTER 
#define ASSIMP_BUILD_NO_LWS_IMPORTER 
#define ASSIMP_BUILD_NO_OGRE_IMPORTER 
#define ASSIMP_BUILD_NO_MS3D_IMPORTER 
#define ASSIMP_BUILD_NO_COB_IMPORTER 
#define ASSIMP_BUILD_NO_NDO_IMPORTER 
#define ASSIMP_BUILD_NO_IFC_IMPORTER 
#define ASSIMP_BUILD_NO_XGL_IMPORTER

#define ASSIMP_BUILD_NO_STL_EXPORTER
#define ASSIMP_BUILD_NO_PLY_EXPORTER
#define ASSIMP_BUILD_NO_EXPORT

// Currently supported formats 
// '*.3ds;*.blend;*.bvh;*.csm;*.dae;*.dxf;*.fbx;*.lwo;*.lxo;*.obj;*.off;*.pk3;*.prj;*.x'

// maybe later: LightWave Scene ( .lws ) and irrlicht meshes and scenes, ogre
// or unreal engine object format (.3d)

// Note:
// Biovision BVH ( .bvh )
// CharacterStudio Motion ( .csm )
// bvh/csm are motion capture formats

#endif // FG_INC_ASSIMP_CUSTOM_CONFIG

