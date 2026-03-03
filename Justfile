set shell := ["bash", "-cu"]

default:
    just --list

build:
    cd build && cmake -G Ninja .. && ninja

run:
    ./build/main_loggirus

exec: build run

clean:
    rm -rf build
