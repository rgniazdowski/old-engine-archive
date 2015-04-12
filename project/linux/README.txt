BUILD PROCESS FOR MULTIPLE PLATFORMS:
------------------------------------

FlexiGame_NB - this folder contains project file for NetBeans IDE.

Simple name FlexiGame(...) indicates that project is for build the whole engine
as one executable file.

Other project files for tools and also for building FlexiGame as a library (or some parts of it
like a library) are planned for the future. The problem currently is however with choosing
the best IDE for that purpose.

NetBeans and Code::Blocks are multiplatform, that's why they're first choice.
NetBeans supports qmake (Qt makefile).

----
Kdevelop is only for linux (-)
Anjuta is just... bad (-)

---
Project for building FlexiGame for mobile platform (via Marmalade) is in file *.mkb.
This requires VisualStudio (Windows) or Xcode (on MacOSX).

To build under WINDOWS:
----------------------

iOS			- Marmalade - Visual Studio
Android		- Marmalade - Visual Studio
windows		- custom - Visual Studio
windows		- custom - NetBeans

To build under MacOSX:
---------------------

iOS			- Marmalade - Xcode
Android		- Marmalade - Xcode
OSX			- custom - Xcode
OSX			- custom - NetBeans
Android		- custom - Xcode

To build under Linux:
--------------------

Linux		- custom - cmake/autoconf/other raw toolchain
Linux		- custom - NetBeans
Android		- custom - Eclipse, AndroidStudio, Android SDK/NDK, gdb, ddd

Can use also other IDE (QtCreator, Eclipse)

