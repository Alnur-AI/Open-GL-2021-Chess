The task was performed on windows

The basic part of the task is fulfilled
1) the game board is displayed
2) Shapes are arranged according to the rules
3) Added functionality to click and select a figure (partially)

1) install clang compiler if you don't have it or don't know what it is.

https://github.com/llvm/llvm-project/releases/tag/llvmorg-12.0.0

Download LLVM-12.0.0.0-win64.exe
And install it in 
C:/Program Files/LLVM 
(default directory)

2) unpack Chess.rar in the D drive.
It will be assumed that you unpacked the archive to D:\Chess.

3) add D:\ChessECS\BuildTools\Ninja to the PATH variable of the user's environment.

4) If you don't have Visual Studio, install Visual studio (only C++ package) - the easiest way to get windows specific libs.

5) compilation

open command line

C:\Users\Admin>d: // go to disk D.

D:\>cd Chess // go to the Chess folder.

D:\Chess>build_script.bat dbg.
// run the compilation batnik
//argument can be either dbg (debug build, without optimizations) or rel (release build, with optimizations).

You should see the following:
Codegen finished work


-- The C compiler identification is Clang 12.0.0 with GNU-like command-line
-- The CXX compiler identification is Clang 12.0.0 with GNU-like command-line
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/LLVM/bin/clang.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/LLVM/bin/clang++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: D:/Chess/Builds/win/dbg
[2/47] Building CXX object Common/CMakeFiles/Engine.dir/Sources/Engine/Render/world_renderer.cpp.obj     


4) run

D:Arcade>run_script.bat dbg


5) VScode
For fast development, we recommend using VScode
It is basically just a text editor, but it can be fully customized and used just like VisualStudio.

https://code.visualstudio.com/download

Necessary extensions:
https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
https://marketplace.visualstudio.com/items?itemName=AlexandrShcherbakov.launchoption

After installing them you can build a sample with ctrl+Shift+B (the hotkey changes)
and run with F5

Translated with DeepL.com (free version)
