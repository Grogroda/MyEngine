# My Physics Engine

This is a personal educational project meant to be worked on for a long time with no pressure at all to grow it fast or known final goal. Eventually it should work as a multi-purpose physics engine, but really my goal is to finish each subproject without caring about what is needed to actually make a useful engine. 

I'll start with a simple path tracer that will work as my renderer, which will require a feel math tools that will be implemented in the src/math/ directory (provisional name), I'll then move on to a fluid simulator and work on how to integrate it with the renderer and how to make animations, and from that point onwards I'm free to implement whatever physical effect I want whenever I want, if I think the learning experience will be constructive or if I think the result might be interesting or useful.

I'm building almost everything from scratch, so that should keep the requirements to run or contribute to this project to a minimum, but here are a few needed tools:

- cpp version: 11.4.0

Project structure:

* bin/: Binary files, organized in subdirectories if needed;
* build/: CMake artifacts (?);
* src/: Source code;
    - core/: Some core utilities such as integrators, vector implementations, etc;
    - physics/: Multiple subdirectories, each with an implementation of a different physical property;
    - tracer/: Path tracer that will be used as renderer, I'll follow [Peter Shirley's "Ray Tracing in One Weekend" guide](https://raytracing.github.io/books/RayTracingInOneWeekend.html) as a guide for this, which results in a quite simple renderer. If I ever want to make it more complex, there are 2 other guides that build on top of this first one [here](https://raytracing.github.io/).
* examples/: Examples of running scripts and their results

