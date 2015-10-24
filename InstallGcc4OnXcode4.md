# Introduction #

Here you can find instructions on how to install GCC 4.0 and older SDKs on Xcode 4 series.

First of all a big question: why human beings are always searching for pain?

Because human beings are essentially evil, so they have to suffer. Or maybe not.

Anyway, here are the steps I followed.


# Step 1: Obtain Xcode 3 #

Ok, that's not a joke. If you want to install older stuffs on Xcode 4 you have to obtain Xcode 3 in some way, because you can find what you need only in a Xcode 3 installation.

As far as I know, Apple doesn't provide these stuffs on the developer website; I read somewhere that only registered and paying developers can download old material, but let me know if I'm wrong.

I copied what I needed from a 2007 MacBook Pro with Snow Leopard and Xcode 3.

# Step 2: Installing GCC 4.0 #

Here the shopping list:
  * binaries: `c++-4.0`,  `cpp-4.0`,  `g++-4.0`, `gcc-4.0`, `gcov-4.0`, `i686-apple-darwin10-g++-4.0.1`, `i686-apple-darwin10-gcc-4.0.1`, `powerpc-apple-darwin10-g++-4.0.1` and `powerpc-apple-darwin10-gcc-4.0.1`
  * libexec directories: `i686-apple-darwin10` and `powerpc-apple-darwin10`
  * xcplugin: `GCC 4.0.xcplugin`

Just dive into a Xcode 3 installation or into a pre Lion installation CD/DVD to find them all (a little hint: `/Developer` is a good starting point).

From Xcode 4, all the binaries and libraries are included in the Xcode bundle; someone say that Xcode can find them also when placed on external paths, but in my case this didn't work, so I've installed everything in the Xcode's belly.

Open the finder, find Xcode bundle and show its contents! You have to place the binaries in:
```
Xcode.app/Contents/Developer/usr/bin
```
the libexec directories in
```
Xcode.app/Contents/Developer/usr/libexec/gcc
```
and the plugin in
```
Xcode.app/Contents/PlugIns/Xcode3Core.ideplugin/Contents/SharedSupport/Developer/Library/Xcode/Plug-ins
```

Now, thanks to the its modular structure, when you restart Xcode you should find as alternative compiler `GCC 4.0`.

# Step 3: Installing SDKs #
From same _source_ that gives you all the gcc 4.0 wonders, pick the SDK bundles, named:
  * MacOSX10.4u.sdk
  * MacOSX10.6.sdk
and place them in
```
Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs
```

Now, when you restart Xcode, freshly installed SDKs will become available.