#Random Tests

This directory contains the code for a work in progress blog / article about the new [C++ 11 random library](http://en.cppreference.com/w/cpp/numeric/random). 

The aim of these tests is to explore the different number generators and distribution functions with respect to visual impact / image generation. 

The plan is to use the original rand() functions as a basis then use different tests using [perlin noise](https://en.wikipedia.org/wiki/Perlin_noise) as well as other visually interesting subjects (flocking for example) to see how the different functions can be used to get different effects.

As I said this is work in progress so the code is at best a mess and usually much wores.

##[Noise](https://github.com/NCCA/RandomTests/tree/master/Noise)
This demo is the basic noise class using C++ 11 to generate a classic perlin noise table (using a lookup size of 256 / unsigned char). This is based on the implementation in the book [Texturing and Modelling a Procedural approach](http://www.csee.umbc.edu/~ebert/book2e.html) but updated for C++ 11

##[NoiseTemplated](https://github.com/NCCA/RandomTests/tree/master/NoiseTemplated)
This example makes the Noise class a template which allows us to generate larger table sizes, It can use up to unsigend int 32 bit table sizes, however this is really slow as we have over 4 billion entries (4294967296) and with the floating point table takes about 30 GB of memory.
