FlexiGame - this folder contains code::blocks project file.
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


-----------------------
To build under WINDOWS:

For iOS - Marmalade - Visual Studio
For Android - Marmalade - Visual Studio

For windows - custom - Visual Studio
For windows - custom - NetBeans
For windows - custom - Code::Blocks

----------------------
To build under MacOSX:

For iOS - Marmalade - Xcode
For Android - Marmalade - Xcode

For OSX - custom - Xcode
For OSX - custom - NetBeans

---------------------
To build under Linux:

For iOS - Marmalade - NO YOU CANT (use virtual machine, back to windows)
For Android - custom - Android SDK IDE - NOT PLANNED

For linux - custom - cmake/autoconf/other raw toolchain
For linux - custom - NetBeans
For linux - custom - Code::Blocks

Can use also other IDE (QtCreator, Eclipse)
