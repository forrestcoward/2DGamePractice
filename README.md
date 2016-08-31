**Description**

This is a sample [SDL](http://www.libsdl.org/) application developed using Visual Studio.

**Setup Instructions (before SDL was checked in)**

1. Download the [SDL2 development library](http://www.libsdl.org/download-2.0.php) for Visual C++ 32/64-bit

2. Download the [SDL2_image developement library](https://www.libsdl.org/projects/SDL_image/) for Visual C++ 32/64-bit

3. Combine the content of the ``/include`` and ``/lib`` directories of downloads and place them in a known location on your file system. These directories (with the combined content) are referred to as ``/include`` and ``/lib`` in step 5 and 6.
   
4. Clone this project and open the solution inside Visual Studio 2012 or 2013

5. Next, you need configure the C++ compiler/linker to find the SDL libraries. Navigate to ``Properties -> Configuration Properties`` for the SDL_Samples project:

	- Add ``/include`` to ``C/C++ -> General -> Additional Include Directories``
	- Add ``/lib/x86`` to ``Linker -> General -> Additional Library Directories``
	- Add ``SDL2main.lib``, ``SDL2.lib`` and ``SDL2_image.lib`` to ``Linker -> Input -> Additional Dependencies``
	- Change ``Linker -> System -> SubSystem`` to Console or Windows
	
6. After building and attempting to run the 'SDL_Samples' project, Visual Studio will complain about missing libraries. Copy the .dll files from ``/lib/x86`` to the output directory to fix this.

7. Having trouble? You can also see [setup SDL in Visual Studio 2015](http://headerphile.com/sdl2/sdl2-part-0-setting-up-visual-studio-for-sdl2/)

