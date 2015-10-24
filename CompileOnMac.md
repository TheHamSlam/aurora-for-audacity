# How to compile on Mac #

In the source tree you can find two projects, one for Xcode 3 and the other for Xcode 4 series. The first is the preferred ones, but I'm working on the latter because I like Xcode 4 and I want to make things work on this environment.

But, the hardest things are the libraries compilation processes...

Take a coffe, then we'll start.

# Step 0: Xcode #
If you have Xcode 3, you are quite ok, so relax; if you have Xcode 4, you have to prepare yourself to a very zen task: breathe slowly and don't let yourself be overwhelmed by anger. First of all, what you need:
  * OSX SDK 10.4
  * OSX SDK 10.6
  * GCC 4.0
as you maybe know neither is included in Xcode 4 and the LLVM compiler family cannot build Audacity. As you are imagining you have to install both by yourself. By hand! Because since they are unsupported, Apple doesn't tell you how to install, but you can. Of course you can!

Just read here: [InstallGcc4OnXcode4](InstallGcc4OnXcode4.md).

# Step 1: Dependencies #

Now it's supposed you have a Gcc 4.0 working compiler on your machine, now only three dependencies are required:

  * **wxWidgets 2.8.12** (http://wxwidgets.org/downloads)
  * **Audacity** (http://audacity.sourceforge.net/download/source)
  * **FFTW3** (http://www.fftw.org/download.html)

## Installing wxWidgets ##
From the website you can easily download the binaries, but if you want to build _Aurora for Audacity_ you need also the sources and if you want to develop a bit you have to build them! Well, download sources (wxAll or wxMac) and unpack them.

Now the tricky part: to develop _Aurora for Audacity_ it's better to compile the libraries in both shared & static version in release & debug configurations. Open a terminal, go into wxWidgets root source tree and create four directories: `build-shared`, `build-shared-debug`, `build-static` and `build-static-debug`.
Go into the first, create a text file named `build-cmd` with the following contents:
```
#! /bin/bash

arch_flags="-arch i386"
debug_flags= #"--enable-debug"
static_flags= #"--disable-shared"

SDK_PATH=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.6.sdk
VERSION=10.4

../configure  --enable-unicode $debug_flags $static_flags --prefix=/opt/local --with-macosx-sdk=$SDK_PATH  --with-macosx-version-min=$VERSION CFLAGS="$arch_flags" CXXFLAGS="$arch_flags" CPPFLAGS="$arch_flags" LDFLAGS="$arch_flags" OBJCFLAGS="$arch_flags" OBJCXXFLAGS="$arch_flags"
```
then give execution permissions and launch it. After it has finished, `make`, then `sudo make install`.

Go to `build-shared-debug`, copy there the script `build-cmd` and remove from line **4** the hashtag and the space before it; launch the script, `make`, then `sudo make install`.

Go to `build-static` copy the script from `build-shared` and remove from line **5** the hashtag and the space before it; launch the script, `make`, then `sudo make install`.

Go to `build-static-debug` copy the script from `build-static` and remove from line **4** the hashtag and the space before it; launch the script, `make`, then `sudo make install`.

Now if you look into the `/opt/local/lib`path, you should find a complete wxWidgets libraries set:)

Remeber: version **2.8.12**.

### Why 10.6 SDK? ###
Yes, why we need 10.6 SDK? Well, it's a sort of compromise that works well for me: I develop on a Lion machine with Xcode 4 and, as you probably know, since 10.7 _Carbon_ programming interface is deprecated by Apple. The wxWidgets 2.8 libraries, however, are based on _Carbon_ interface, then 10.6 is the last SDK supporting _Carbon_ and supported by the default compiler!

I think you can use 10.4 SDK, but it's a 32 bit libraries set and recent (64 bit) compilers don't support it, so you have to modify the script and tell _configure_ to use `GCC 4.0` or 4.2 if you have it.

wxWidgets 2.8 on OSX environment is still a 32 bit library, newest 2.9 serie is 64 bit too and Cocoa based but Audacity developers prefer good old stable 2.8. Modules has to follow necessarily this way.

## Installing Audacity ##
If you are here you should have Audacity installed on your system, but if you want to build _Aurora for Audacity_ you need Audacity sources too. So, download the full source tree from the website and unpack it on your machine.
If you have Xcode 3, you can use the included project and the building instruction that you find on the website. You can build only the Debug configuration.

If you have Xcode 4...we're working on it: the compiling process is quite complete but still some annoying errors to remove.

### Version ###
Actually the last working is **2.0.1** but some really nice
people is working to get _Aurora for Audacity_ on the very last release of Audacity.

## Installing FFTW3 ##
Download latest sources from the website and unpack them. Open a terminal, go into FFTW3 root source tree and create two directories: `build`, `build-single`
Go into the first, create a text file named `build-cmd` with the following contents:
```
#! /bin/bash

PREFIX=/opt/local
arch_flags="-arch i386 -mtune=core2"
ld_flags="-Wl,-arch -Wl,i386"
single_flags= #"--enable-single"

../configure CFLAGS="$arch_flags" CXXFLAGS="$arch_flags" CPPFLAGS="$arch_flags" LDFLAGS="$ld_flags" OBJCFLAGS="$arch_flags" OBJCXXFLAGS="$arch_flags" --prefix=$PREFIX --libdir=$PREFIX/lib $single_flags --enable-shared
```
then give execution permissions and launch it. After it has finished, `make`, then `sudo make install`.

Go to `build-single`, copy there the script `build-cmd` and remove from line **6** the hashtag and the space before it; launch the script, `make`, then `sudo make install`.

Now if you look into the `/opt/local/lib`path, you should find a complete FFTW3 libraries set:))

# Step 2: Edit Properties #
Before starting the _Aurora for Audacity_ building process there are some very boring checks to do. Start Xcode, then open the Aurora project in `osx` subdir. Open the main project properties/Info/Build settings and look at the bottom for the user defined macros. You should check only
  * `AUDACITY_BINARY_PATH`
  * `AUDACITY_SRC_PREFIX`
and eventually change its contents according to your installation. Look around a bit if everything is ok then close the dialog: the other projects/targets should have inherited the changes, so you can start building things.

# Step 3: Build #
Nothing to say. Select one target and build it.

# Step 4: Debugging #
To develop Audacity module, it's strongly recommended a well configurated debug environment; but it's not so difficult: you have to specify who is the executable in the targets' Scheme/Run configuration. Obviously the executable is Audacity compiled with debug symbols!

At this point when you press the debug button in the project, Audacity starts and you can use
breakpoints & friends in the module and Audacity code too (it is sufficient that you add to the project the audacity code files where you want setup breakpoints). Very useful when Audacity doesn't load the modules...

Have fun!