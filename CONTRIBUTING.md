# Contributing
splinepy welcomes and appreciates discussions, issues and pull requests!

## Quick start
Once the repo is forked, one possible starting point would be creating a new python environments, for example, using [conda](https://docs.conda.io/en/latest/miniconda.html) with `python=3.9`
```bash
conda create -n splinepyenv python=3.9
conda activate splinepyenv
git clone git@github.com:<path-to-your-fork>
cd splinepy  # or <forkname>
git submodule update --init --recursive
git checkout -b new-feature0
python3 setup.py develop --minimal
```
`--minimal` flag builds splines upto 3D (both parametric and physical dimensions), and that way we can reduce compile time. We are experimenting with the ways to reduce compile time during development. Let us know if you have a great idea!

## Python style / implementation preferences
- use `if` and `raise` instead of `assert`
- no complex comphrehensions: preferably fits in a line, 2 lines max if it is totally necessary
- use first letter abbreviations in element loops:  `for kv in knot_vectors`
- use `i`, `j`, `k`, `l` for pure index: `for i, kv in enumerate(knot_vectors)`

## C++ style / implementation preferences
For c++, we've prepared a `.clang-format`, with that you can just run `clang-format`. We closely follow naming scheme suggested by [google stype guide](https://google.github.io/styleguide/cppguide.html#Naming), with a clear exception of file naming.
Here's a preference:
- `#pragma once`

## Automatic formatting / style check
To check the format and style of your code use the following commands:
```bash
pip install pre-commit
precommit run -a
```