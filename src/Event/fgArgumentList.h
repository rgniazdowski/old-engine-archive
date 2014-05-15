/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _ARGUMENT_LIST_H
#define _ARGUMENT_LIST_H

#include <vector>

#define FG_ARGUMENT_DEFAULT_COUNT	8
#define FG_ARGUMENT_MAX_STRING		256

enum fgArgumentType
{
	FG_ARGUMENT_INTEGER,
	FG_ARGUMENT_DOUBLE,
	FG_ARGUMENT_FLOAT,
	// Char string array
	FG_ARGUMENT_STRING,
	// Void* pointer to any kind of data
	FG_ARGUMENT_POINTER,
	// Pointer to allocated structure, structure needs to be allocated by 'malloc' and freed using the 'free' function
	FG_ARGUMENT_STRUCT,
	FG_ARGUMENT_NONE
};

struct fgArgument
{
	fgArgumentType type;
	union
	{
		int int_val;
		double double_val;
		float float_val;
		char string[FG_ARGUMENT_MAX_STRING];
		void *custom_pointer;
	};

	fgArgument() : type(FG_ARGUMENT_NONE), int_val(0) {
	}

	void reset() {
		type = FG_ARGUMENT_NONE;
		int_val = 0;
	}
};

class fgArgumentList
{
	private:
		std::vector<fgArgument> m_argv;
		int m_argc;
		int m_maxArgs;
		int m_currentArg;
		fgArgument m_emptyArgument;
	public:
		fgArgumentList();
		fgArgumentList(int _max);

		~fgArgumentList();

		inline void setMaxArgumentCount(int _max);
		inline int getMaxArgumentCount();

		void pushArgument(fgArgumentType _type, void *_value);
		void pushArgument(int int_val);
		void pushArgument(double double_val);
		void pushArgument(float float_val);
		void pushArgument(const char *string);
		void pushArgument(void *custom_pointer);

		inline int getArgumentCount();

		inline void reset();
		inline bool isThereNextArgument();

		void *getNextArgumentValue(fgArgumentType *_type);
		void *getArgumentValueByID(int ID, fgArgumentType *_type);

		fgArgument getNextArgumentStruct();
		fgArgument getArgumentStructByID(int ID);

		inline int getCurrentID();

		void clearArguments();

		inline fgArgument &operator[](int i) { m_emptyArgument.reset(); if((int)m_argv.size() > i) return m_argv[i]; else return m_emptyArgument; }
		inline const fgArgument operator[](int i) const { if((int)m_argv.size() > i) return m_argv[i]; else return m_emptyArgument; }
};


#endif


