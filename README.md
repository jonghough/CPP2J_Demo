# CPP2J_Demo
Demo game using SDL 2.0 library and using J to handle the logic while C++ / SDL handles UI and events.


What is this?
---

This is a demonstration app that shows how to use the libj.so (j.dll on Windows) API from C++. The API functions used are

* `JInit` used to initialize a J instance.
* `JDo` used to execute some J command.
* `JGetM` returns the result of `JDo`
* `JFree` free up the memory

references:
> http://www.jsoftware.com/help/user/calling_jdll.htm

> http://www.jsoftware.com/help/user/call_procedure.htm

> http://www.jsoftware.com/pipermail/programming/2013-June/032979.html


The application is a simple game creates using the SDL 2.0 library, along with the SDL2_image library. The game is controlled by the UP, DOWN, LEFT, RIGHT arrow keys, to rotate columns and rows of a 5x5 grid of coloured squares. To move between the columns and rows, use the A,D keys to move left or right, and the W,S keys to move up and down.

The goal of the game is to make all the squares in each row have the same colour. (i.e. a rubik's square)

What's this got to do with J?
---

Rotating columns and rows of a grid are not a difficult task in probably all programming languages, but in J the task becomes trivial. And to setup a random grid, the function also becomes simple (i.e. one line).

For instance, to initialize the randomized grid (of five colours, labelled 0,...,4):

`arr =: ([ ? #/~) 5`

to rotate rows:

`arr =:( 1 |. 0 {"2 arr) 0 }"2 arr`

By allowing some of the logic to be performed in J, development speed can be increased. For example, this may be useful in prototyping, and is not limited to games.

To call procedures from the libj.so shared library, dlopen must be used on Linux systems.
