LuaPlus for Marmalade
=====================

LuaPLus is mainly intended to wrap c++ classes in lua script.
But unlike luabind it makes some significant modifications in source lua code.
Due this LuaPlus is a little faster, more convenient and much more powerfull than pure lua is.

This folder contains the mkf file for integrate
LuaPlus into your Marmalade project.

Original LuaPlus homepage is: http://luaplus.org

The LuaPlus source is compiled completely unmodified
(but a pair of file is not necessary and they are not included in luaplus.mkf).

To include LuaPlus into your project, put the luaplus directory within your project directory.
Then you'll need to add this LuaPlus subproject and the include path to it:

subprojects
{
    ./luaplus
}


includepath
{
    ./luaplus
}

Some LuaPLus examples can be found on the LuaPLus homepage (http://luaplus.org).
Although there are some great titles created with LuaPlus (Supreme Commander FA, UFO2000 and some others),
it is acceptable to use LuaPlus on mobile devices without any significant performances penalties.