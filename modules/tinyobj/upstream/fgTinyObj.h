//
// Copyright 2012-2013, Syoyo Fujita.
//
// Licensed under 2-clause BSD liecense.
//
#ifndef FG_INC_TINY_OBJ_LOADER_H_
    #define FG_INC_TINY_OBJ_LOADER_H_

    #include <string>
    #include <vector>
    #include <map>

    #include "GFX/fgGfxMesh.h"
    #include "Util/fgFile.h"

namespace fgTinyObj {

    /**
     * 
     */
    class MaterialReader {
    public:
        /**
         * 
         */
        MaterialReader() { }
        /**
         * 
         */
        virtual ~MaterialReader() { }
        /**
         * 
         * @param matId
         * @param matMap
         * @return 
         */
        virtual std::string operator ()(
                const std::string& matId,
                std::map<std::string, fg::gfx::SMaterial>& matMap) = 0;
    };

    /**
     * 
     */
    class MaterialFileReader : public MaterialReader {
    public:
        /**
         * 
         * @param mtl_basepath
         */
        MaterialFileReader(const std::string& mtl_basepath) : m_mtlBasePath(mtl_basepath) { }
        /**
         * 
         */
        virtual ~MaterialFileReader() { }
        /**
         * 
         * @param matId
         * @param matMap
         * @return 
         */
        virtual std::string operator ()(
                const std::string& matId,
                std::map<std::string, fg::gfx::SMaterial>& matMap);

    private:
        ///
        std::string m_mtlBasePath;
    };

    /// Loads .obj from a file.
    /// 'shapes' will be filled with parsed shape data
    /// The function returns error string.
    /// Returns empty string when loading .obj success.
    /// 'mtl_basepath' is optional, and used for base path for .mtl file.
    std::string LoadObj(fg::CVector<fg::gfx::SShape *>& shapes, // [output]
                        const char* filename,
                        const char* mtl_basepath = NULL,
                        fgBool forceAoS = FG_TRUE);

    /// Loads object from a std::istream, uses GetMtlIStreamFn to retrieve
    /// std::istream for materials.
    /// Returns empty string when loading .obj success.
    std::string LoadObj(fg::CVector<fg::gfx::SShape *>& shapes, // [output]
                        fg::util::CFile& inputFile,
                        MaterialReader& readMatFn,
                        fgBool forceAoS = FG_TRUE);

    /// Loads materials into std::map
    /// Returns an empty string if successful
    std::string LoadMtl(std::map<std::string, fg::gfx::SMaterial>& material_map,
                        std::istream& inStream);
}

#endif  /* FG_INC_TINY_OBJ_LOADER_H_ */
