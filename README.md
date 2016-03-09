#Random Tests

This directory contains the code for a work in progress blog / article about the new [C++ 11 random library](http://en.cppreference.com/w/cpp/numeric/random). 

The aim of these tests is to explore the different number generators and distribution functions with respect to visual impact / image generation. 

The plan is to use the original rand() functions as a basis then use different tests using [perlin noise](https://en.wikipedia.org/wiki/Perlin_noise) as well as other visually interesting subjects (flocking for example) to see how the different functions can be used to get different effects.

As I said this is work in progress so the code is at best a mess and usually much worse.

To run these demos you will need to install [OpenImageIO](https://github.com/OpenImageIO/oiio) as this is used to save images. A C++ 11 compiler is also needed.

Later demos will most likely need to have OpenGL / SDL to work as well and perhaps my NGL library.

##[Noise](https://github.com/NCCA/RandomTests/tree/master/Noise)
This demo is the basic noise class using C++ 11 to generate a classic perlin noise table (using a lookup size of 256 / unsigned char). This is based on the implementation in the book [Texturing and Modelling a Procedural approach](http://www.csee.umbc.edu/~ebert/book2e.html) but updated for C++ 11
##[NoiseRand](https://github.com/NCCA/RandomTests/tree/master/NoiseRand)
Templated Noise class using the old rand() function rather than the new C++ 11 versions so we can see the differences between the generators. This version uses the templated class and C++ 11 lambda's but these use the rand() % style old school c++ random

##[NoiseTemplated](https://github.com/NCCA/RandomTests/tree/master/NoiseTemplated)
This example makes the Noise class a template which allows us to generate larger table sizes, It can use up to unsigend int 32 bit table sizes, however this is really slow as we have over 4 billion entries (4294967296) and with the floating point table takes about 30 GB of memory.
