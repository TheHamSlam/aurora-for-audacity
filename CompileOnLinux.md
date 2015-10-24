# How to compile on Linux #

Here you can find some instructions about the compilation process in a GNU/Linux environment. Please note that the process is not very _automated_ because:
  * I hate autoconf/automake
  * I think anyone should know what is installed on his machine and where it is
the consequence is that some scripting is needed, but not very difficult indeed: instead of passing parameters to a stupid _configure_ script, you have to type them directly into a _scons_ script.

So let's start!


# Step 1: Dependencies #

Only four dependencies are required:

  * **SCons** (http://www.scons.org)
  * **wxWidgets 2.8.12** (http://wxwidgets.org/downloads)
  * **Audacity** (http://audacity.sourceforge.net/download/source)
  * **FFTW3** (http://www.fftw.org/download.html)

## Installing SCons ##
I use SCons because I already know Pyhton and I don't want to
learn another scripting language. The good news is that SCons is really cool, simple and well structured, so what else you need?
Installing SCons should be really straightforward: find it on your distribution installer and pick the last version. Done.

## Installing wxWidgets ##
You can install it from your distribution installer too, obviously not only the libraries but also the development package (that usually includes headers and others useful stuffs).
If you plan to develop a bit with _Aurora for Audacity_ I suggest also to install the libraries with debug symbols: these can come very handy...
If your distribution doesn't provides a wxGTK package with debug symbols, you can compile it by yourself from the sources you can find on the wxWidgets website: follow the compilation instructions and add the 'debug' parameter to _configure_ script (_configure --help_ gives you the full list).
Remeber: version **2.8.12**. Stop.

## Installing Audacity ##
If you are here you should have Audacity installed on your system, but if you want to build _Aurora for Audacity_ you need Audacity sources too. So, download the full source tree from the website and unpack it on your machine.
Like wx, if you want to develop is very **strongly** recommended to compile Audacity with debug symbols and - luckily - this is quite simple: give the 'debug' parameter to _configure_ script!

Note: if your configure script hangs because it doesn't find some libraries like MAD, ffmpg, etc. you can disable them from the compilation process, because _Aurora for Audacity_ doesn't need these.

### Version ###
Actually the last working is **2.0.1** but some really nice
people is working to get _Aurora for Audacity_ on the very last release of Audacity.

## Installing FFTW3 ##
Install it with you package manager, double and single precision. You don't need debug version.

# Step 2: Edit SConscript #

Do you want to use GNU/Linux? Then script!
I'm a Linux user since years and I love its nerdy approach, so if you want to compile _Aurora for Audacity_, open the _SConscript_ script
you find in the source root with your favourite editor and, first of all, check the following variables:
  * `audacity-src-path`
  * `aurora_src_prefix`
  * `audacity_modules_path`
  * `wx_libs`
obviously their content should match what is on your machine! A quick look around is also good, because there are a lot of variables that reflects the installation on my system.

# Step 3: Build #

The _SConscript_ script has many target, listed in the `aurora_modules` variable, so you can type, i.e.
```
 scons AcParameters
```
and the module _AcParameter_ will build in Release configuration. If you want to build a module with debug symbols you have to type, instead,
```
 scons AcParameters config=debug
```

## Where is my module? ##
Yes, where are placed the build products? You can find it in:
```
${HOME}/Development/Aurora/linux/<Release || Debug>/modules
```
Why? Because in this way the source tree will be always **clean**.
If you don't like this, you can modify the variable `build_dir`.

# Step X: The Eclipse Way #
A visual development system is really a nice stuff, especially during the debugging process; I developed for years with console + ddd, but when I used for a while VisualC++ and XCode, ok, there is no discussion: a visual environment can **really** speed up things a lot!
After some other trials (KDevelop, etc) I've choosed Eclipse, and for this reason you can find in the _Aurora for Audacity_ source tree an Eclipse workspace, located in the `eclipse` directory of the main source tree.

## What you need ##
Eclipse Juno. Steps 1 and 2 complete. Then you have to install the full _CDT_ Eclipse plugin, plus the _SConsolidator_ plugin (http://sconsolidator.com/)

With this workspace I can not only build, but also debug the modules: you have only to setup the 'Debug' configuration with the path of your Audacity (with debug symbols...) executable.
When I'll have time I'll add some pictures of this configuration.

That's all.