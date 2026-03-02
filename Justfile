set shell := ["bash", "-cu"]

default:
    just --list

build:
    cd build && cmake -G Ninja .. && ninja

run:
    ./build/main

exec: build run
