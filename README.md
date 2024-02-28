# Majestic

## Storyline

Majestic is a sample GUI client for use with another [sample server](https://github.com/mehrshad-kh/MajesticServer) using gRPC as its interface. It is written entirely in C++ with the help of Qt Widgets. It also makes extensive use of CMake for build automation.  

I started this project as a means to extend my knowledge in the realm of C++, including the language itself, the Qt framework, CMake, and other extensively used tools and APIs. Through the journey, I also reported a [bug](https://bugreports.qt.io/browse/QTCREATORBUG-29478) in Qt Creator and helped discover [another one](https://bugreports.qt.io/browse/QTCREATORBUG-29450)(more discussions [here][1] and [here][2]).

## Demo
![alt test](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExYXhwNDhkeGh6eDlvbXYzOHd2NHNqeXBvd24yMGVkZzl3YTY0c3RibCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Lox6BBCeJr8IYotIni/giphy.gif)

## Prerequisites

- [Argon2](https://github.com/P-H-C/phc-winner-argon2) for hashing user passwords
- [`fmt`](https://fmt.dev/latest/index.html) formatting library, as the project uses C++17 entirely
- [gRPC](https://grpc.io/)
- `pkg-config`
- [Protocol Buffers](https://protobuf.dev/)
- [Qt 6](https://www.qt.io/product/qt6)

## How to Run

You may run `cmake.run` from the command-line. As I use a Mac, `CMAKE_PREFIX_PATH` is set to the default Qt installation on macOS. You may change it accordingly.  
Afterwards, you can run `ninja.run` to build the app. You can then find it as `build/Majestic.app`.

[1]: https://forum.qt.io/topic/147297/clang-code-model-doesn-t-work-when-using-cmake/8?lang=en-US
[2]: https://forum.qt.io/topic/107181/lot-of-errors-but-it-builds-and-runs-successfully



