# How to compile on Windows #

Like the Audacity building process, this is based on a **VisualC++ 2008** solution, so if you want to build it, you have to obtain, i.e., VisualC++ 2008 Express that is free and includes everything you need.

The _Aurora for Audacity_ solution doesn't work with VisualC++ 2010, nor 2013, or newest, so if you want to build it on these environment there is no support at all. When Audacity will switch to a new Visual IDE, maybe I'll think about it...

Let's crackin'.


# Step 1: Dependencies #

Only three dependencies are required:

  * **wxWidgets 2.8.12** (http://wxwidgets.org/downloads)
  * **Audacity** (http://audacity.sourceforge.net/download/source)
  * **FFTW3** (http://www.fftw.org/download.html)

## Installing wxWidgets ##
From the website you can easily download the binaries, but if you want to build _Aurora for Audacity_ you need also the sources and if you want to develop a bit you have to build them! Well, what you have to do is:
  * download sources (wxAll or wxMSW)
  * compile them using the VC++ 2008 solution that you can find in `build/msw` subdirectory.
For developing purposes it's a good choice to compile both Release & Debug configurations. Shared.
Remeber: version **2.8.12**.

## Installing Audacity ##
If you are here you should have Audacity installed on your system, but if you want to build _Aurora for Audacity_ you need Audacity sources too. So, download the full source tree from the website and unpack it on your machine.
Like wx, if you want to develop is very **strongly** recommended to compile Audacity with debug symbols: you can use the included VC++ 2008 solution, located in the `win` subdirectory.

### Version ###
Actually the last working is **2.0.1** but some really nice
people is working to get _Aurora for Audacity_ on the very last release of Audacity.

## Installing FFTW3 ##
In this page http://www.fftw.org/install/windows.html you can find precompiled binaries and a cool VC++ 2008 project ready to compile, so use it! No debug version required here.

# Step 2: Edit Properties #
Before starting the _Aurora for Audacity_ building process there are some very boring checks to do. Start VC++ 2008, then open the Aurora solution located in `win32` subdir. As you can see, every module has its own project and every project has its own properties; because I don't know how to do some sort of _hierarchical_ properties dependencies (as I usually do with Xcode), where you can set the properties for the _main_ project then all the others inherit them, you have to check every module. If you know how to do in a clever way, please write me.

Anyway here the steps _for dummies_, where all paths are referred to a single project _Configuration Properties_ tree:
  * set the Windows environment variable AUDACITY\_SRC that points to the Audacity source path
  * set the Windows environment variable AUDACITY\_BIN that points to the system installed Audacity (i.e. `C:\Program Files\Audacity-x.y.z`
  * `C/C++/General/Additional Include Directories`:  check for the correctness of all include paths, wxWidgets, Audacity & FFTW3 if required
  * `Linker/General/Additional Library Reference`:   check for the correctness of all .lib files paths; usually you can find there in their visualC++ project directory, i.e. `C:/wxWidgets-2.8.12/lib/vc_dll`
  * `Linker/Additional Dependencies`: check for the existence of all required .lib files.

## Note ##
It was reported that in some projects something is missing, precisely `Properties/Linker/Input/Additional Dependencies` should contains the following libraries `wxbase28ud.lib`, `wxbase28ud_net.lib`, `wxmsw28ud_adv.lib`, `wxmsw28ud_core.lib` and `wxmsw28ud_html.lib`. If these names wasn't shown, add them to the field. Obviously these files must be present in your wxWidgets debug build directory.

# Step 3: Build #
Nothing to say. Simply build it.

# Step 4: Debugging #
To develop Audacity module, it's strongly recommended a well configurated debug environment; if you have successfully compiled Audacity & wxWidgets in debug configuration you are at 90%, now you have to copy the wxWidgets dll files in the same directory of the Audacity (debug) executable, then reopen a project Properties panel in the _Aurora for Audacity_ solution, go to `Debug` branch and fill the _Command_ field on the right with the Audacity executable full path, something like `C:/audacity-src-2.x.y/win/Unicode Debug/Audacity.exe`.

At this point when you press the debug button in the plugin project, Audacity starts and you can use
breakpoints & friends in the module and Audacity code too (it is sufficient that you add to the project the audacity code files where you want setup breakpoints). Very useful when Audacity doesn't load the modules...

Enjoy!