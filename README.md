# README

## Description

This is an implementation of the dancing links algorithm 
(https://arxiv.org/abs/cs/0011047) for solving exact cover problems, and a
sudoku solver given as an example usage. 

A preliminary benchmark on the 17 clue dataset (copy given in the data/ dir) 
gives 8976 puzzles/sec, which i think is not bad for a first version.

The solver (including sudoku) was implemented first in python (see python/ 
folder), as at the time of starting this project i wasn't confident enough 
in my C skills.

I'm using this mainly as a playground for improving my C skills.

## Building / usage

For building:

```bash
$ cd src/c/dlx 
$ mkdir -p build/Release
$ cd build/Release
$ cmake -DCMAKE_BUILD_TYPE=Release ../.. # or -DCMAKE_BUILD_TYPE=Debug in another dir, or both... check cmake manual
$ cmake --build .
```

This will make both project and tests. Tests depends on the Criterion library
(https://github.com/Snaipe/Criterion, packages available at least for ubuntu
22.04).

To run tests just ctest from the created build/Release dir:

```bash
$ ctest
```

To disable building tests, substitute the first cmake command above for the
following:

```bash
$ cmake -DENABLE_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ../..
```

## TODO

A disordered list of tasks as comes to mind would be:

- Give it a full code review targeting:
  * Refactor type / var / function naming to module_feature_XXX style.
  * Follow a code style guide.
- Refactor python implementation to follow the same naming and directory
  structure as the C version. Give reference to Ali Assaf's solver and mention
  about (poor) performance of the python solver in this readme.
- Can I use some solving strategies for sudoku (e.g. hidden/naked singles) and
  fallback to dlx search? Can i make the apis compatible with this being a 
  general dlx solver?
- Try compiling with CLang (should be no problem).
- Learn to debug Criterion tests, developing via TDD is very disconfortable
  right now.
- Just for the sake of learning, doxygen this, include CI pipeline, versioning,
  etc. Use this to learn to manage a small C project.
- Valgrind this! Probably some memory leaks for now.
- Benchmark this against other sudoku solvers and DLX solvers (see 
  https://github.com/t-dillon/tdoku). Do the best i can with performance,
  and learn to use a profiling tool.
- Improve error management and checking, actual version is maybe a bit dirty.
- Build dlx solver as a separated shared library, and give some more examples
  apart from sudoku. Follow knut's paper for that.
- Rethink some APIs, concretely the search() callback API, which makes 
  difficult to pass additional properties apart from dlx ones (see sudoku)
  to the callback using a stablished API instead of global vars. Another thing
  to think better about is memory management. See for example how DLX grid's
  nodes are freed now in tests and sudoku.

## Licence

MIT. See [LICENCE](LICENCE) file.
