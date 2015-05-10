/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_ARGUMENT_LIST
    #define FG_INC_ARGUMENT_LIST
    #define FG_INC_ARGUMENT_LIST_BLOCK

    #include "fgTypes.h"

    #define FG_ARGUMENT_DEFAULT_COUNT	8
    #define FG_ARGUMENT_MAX_STRING	256 // #FIXME

namespace fg {
    namespace event {

        /**
         *
         */
        struct SArgument {

            enum class Type : unsigned char {
                /// Integer
                ARG_INTEGER,
                /// Double number
                ARG_DOUBLE,
                /// Float number
                ARG_FLOAT,
                /// Char string array
                ARG_STRING,
                /// Void* pointer to any kind of data
                ARG_POINTER,
                /// Pointer to allocated structure, structure needs to be allocated by 'malloc' and freed using the 'free' function
                ARG_TMP_POINTER,
                /// No argument
                ARG_NONE
            } type;

            union {
                /// Value representing integer
                int int_val;
                /// Double precision float value
                double double_val;
                /// Float value
                float float_val;
                /// String parameter
                char string[FG_ARGUMENT_MAX_STRING];
                /// Custom pointer
                void *custom_pointer;
            };
            /**
             * 
             */
            SArgument() : type(Type::ARG_NONE), int_val(0) { }
            /**
             * 
             */
            void reset(void) {
                type = Type::ARG_NONE;
                int_val = 0;
            }
        };

        /**
         *
         */
        class CArgumentList {
        private:
            ///
            fg::CVector<SArgument> m_argv;
            ///
            unsigned int m_maxArgs;
            ///
            int m_currentArg;
            ///
            SArgument m_emptyArgument;

        public:
            /**
             * 
             */
            CArgumentList();
            /**
             * 
             * @param _max
             */
            explicit CArgumentList(unsigned int max);

            /**
             * 
             */
            virtual ~CArgumentList();

            /**
             * 
             * @param _max
             */
            void setMaxCount(unsigned int max);
            /**
             * 
             * @return 
             */
            unsigned int getMaxCount(void) const;

            /**
             * 
             * @param _type
             * @param _value
             */
            void push(SArgument::Type type, void *value);
            /**
             * 
             * @param int_val
             */
            void push(int int_val);
            /**
             * 
             * @param double_val
             */
            void push(double double_val);
            /**
             * 
             * @param float_val
             */
            void push(float float_val);
            /**
             * 
             * @param string
             */
            void push(const char *string);
            /**
             * 
             * @param custom_pointer
             */
            void push(void *custom_pointer);

            /**
             * 
             * @return 
             */
            int getCount(void) const;

            /**
             * 
             */
            void reset(void);
            /**
             * 
             * @return 
             */
            fgBool isNext(void) const;

            /**
             * 
             * @param _type
             * @return 
             */
            void *getNextValue(SArgument::Type *type = NULL);
            /**
             * 
             * @param ID
             * @param _type
             * @return 
             */
            void *getValueByID(int ID, SArgument::Type *type = NULL);

            /**
             * 
             * @return 
             */
            SArgument& getNextStruct(void);
            /**
             * 
             * @param ID
             * @return 
             */
            SArgument& getStructByID(int id);

            /**
             * 
             * @param ID
             * @return 
             */
            SArgument const& getStructByID(int id) const;

            /**
             * 
             * @return 
             */
            int getCurrentID(void) const;

            /**
             * This function  frees the memory  held by the  arguments (argv)
             * The rule is that when some value/structure/pointer is put into
             * the argument list it is being managed by the class, so it also
             * needs to be freed in this function.
             */
            void clear(void);
            /**
             * 
             * @param i
             * @return 
             */
            inline SArgument& operator [](int i) {
                m_emptyArgument.reset();
                if((int)m_argv.size() > i)
                    return m_argv[i];
                else
                    return m_emptyArgument;
            }
            /**
             * 
             * @param i
             * @return 
             */
            inline SArgument const& operator [](int i)const {
                if((int)m_argv.size() > i)
                    return m_argv[i];
                else
                    return m_emptyArgument;
            }
        };
    };
};

    #undef FG_INC_ARGUMENT_LIST_BLOCK
#endif /* FG_INC_ARGUMENT_LIST */
