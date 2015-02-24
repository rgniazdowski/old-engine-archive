/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_TAG_HEADER
    #define FG_INC_TAG_HEADER

namespace fg {
    namespace util {
        namespace tag_helper {
            inline unsigned int hash_func_djb(const char *_in) {
                unsigned int hash = 5381;
                unsigned int c = 0;
                if(!_in) {
                    return hash;
                }

                while((c = *_in++)) {
                    hash = ((hash << 5) + hash) + c;
                }

                return hash;
            }
        };
    };
};

    #define FG_TAG_NAME_LEN_MAX	64

    #define FG_TAG_VOID_NAME	"tag{void}"
    #define FG_TAG_VOID_ID		-1

    #define FG_TAG_FUNCTION_NAME(_name) static const char *name(void) { return _name; }
    #define FG_TAG_FUNCTION_ID(_id) static unsigned int id(void) { return _id; }

    #define FG_TAG_FUNCTION_ID_AUTO() static unsigned int id(void) { return fg::util::tag_helper::hash_func_djb(name()); }
    
namespace fg {
    namespace util {

        struct TagVoid {
        };

        struct TagBase {
        };

        template<class _type> struct Tag : TagBase {
        };
    };
};

/**
 * This is a special tag definition macro.
 * Please remember to define it outside of the namespace fg scope.
 * Tag type template will be set inside of the fg namespace.
 */
    #define FG_TAG_TEMPLATE(_tag_type, _tag_name, _tag_id) \
namespace fg { \
namespace util { \
template <> struct Tag<_tag_type> : TagBase { \
	typedef _tag_type _type; \
	FG_TAG_FUNCTION_NAME(_tag_name) \
	FG_TAG_FUNCTION_ID(_tag_id) \
	}; \
        }; \
        }

/**
 * This is a special tag definition macro.
 * Please remember to define it outside of the namespace fg scope.
 * Tag type template will be set inside of the fg namespace.
 */
    #define FG_TAG_TEMPLATE_ID_AUTO(_tag_type, _tag_name) \
namespace fg { \
namespace util { \
template <> struct Tag<_tag_type> : TagBase { \
	typedef _tag_type _type; \
	FG_TAG_FUNCTION_NAME(_tag_name) \
	FG_TAG_FUNCTION_ID_AUTO() \
	}; \
        }; \
        }

FG_TAG_TEMPLATE(TagVoid, FG_TAG_VOID_NAME, FG_TAG_VOID_ID);


/// Special usage macro, evaluates to: struct fg::util::Tag<_tag_type>. 
    #define FG_TAG_TYPE_NAME(_tag_type) struct fg::util::Tag<_tag_type>
/// Evaluates to the type fg::util::Tag<_tag_type>. Useful for fast typedefs definitions
    #define FG_TAG_TYPE(_tag_type)		fg::util::Tag<_tag_type>

#endif /* FG_INC_TAG_HEADER */
