# TF Variable Input Size Experimentation

This repository just contains a couple of different toy examples that I'm using
to experiment with variable input sizes with various embedding methods to see
what works and what doesn't. Currently looking at Tensorflow saved models,
TFLite models, and AOT XLA compiled models.

### Dependencies

Currently, all of the dependencies are coming from the MLGO repository. To use
this repository, just clone [that](https://github.com/google/ml-compiler-opt)
repository, install all of the python dependencies, and run the TFLite build
script in the `./buildbot` directory somewhere on your system to give you a
build of TFLite. After this, everything should be ready (minus maybe some
file paths being in the wrong place), but those should be fixed pretty
easily.

### Working with the examples

All of the examples are currently built using a simple Makefile that also
manages generating all of the models that are used through the examples.
All of the target names within the Makefile should be fairly self
explanatory.
