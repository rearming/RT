#!/usr/bin/env bash

CLANG=$(find /usr /home ~/ -type f -name clang 2>/dev/null)
if [[ "$CLANG" == "" ]]; then
  echo "can't find clang compiler! please, instatll it!"
  exit 1
fi

CMAKE=$(find /usr /home ~/ -type f -name cmake 2>/dev/null)
if [[ "$CMAKE" == "" ]]; then
  echo "can't find cmake! please, instatll it!"
  exit 1
fi

if [[ ! -f "libft/Makefile" ]]; then
  git submodule init
  git submodule update --merge --remote
fi
cd libft || echo "can't find libft directory!"
make
cd ..

if [[ ! -f "lib/jansson/Makefile" ]]; then
  git submodule init
  git submodule update
  cd lib/jansson/ || echo "need to init submodule of jansson!"
  mkdir "build"
  cd build || echo "can't make build directory"
  cmake ..
  make jansson/fast -j 4
fi

#cdmkdir build
#cd build || echo "can't make build directory!"
#cmake -D CMAKE_C_COMPILER="$CLANG" -DCMAKE_BUILD_TYPE=Release ..
#make RT -j 4
#mv RT ..
