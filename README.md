# CAE input file Parser

## Brief

This is a devlib/application that translate CAE input file to an abstract synatx tree.

Depends on [PEGTL](https://github.com/taocpp/PEGTL) and [CLI11](https://github.com/CLIUtils/CLI11) as sbumodules

A quick glance as below:

simple LS-DYNA demo file
```k
*KEYWORD
*TITLE
Simple Sphere Impact on Plate - LSDYNA Example
$--- 1. CONTROL CARDS ---
*CONTROL_TERMINATION
$   endtim    endcyc     dtmin    endeng    endmas
      10.0         0       0.0       0.01.000000E8
*END
```

application will output:
```shell
ROOT(0:0-0:0):
  K::k_title_card(2:1-4:1):
    K::k_title(3:1-3:46):Simple Sphere Impact on Plate - LSDYNA Example
  K::k_card(5:1-8:1):
    K::k_card_name_option(5:1-5:21):
      K::k_card_name(5:1-5:21):*CONTROL_TERMINATION
    K::k_card_8_field_line(7:1-8:1):
      K::k_real_field(7:7-7:11):10.0
      K::k_int_field(7:20-7:21):0
      K::k_real_field(7:28-7:31):0.0
      K::k_real_field(7:38-7:41):0.0
      K::k_real_field(7:41-7:51):1.000000E8
      K::k_empty_field(7:51-7:51):
      K::k_empty_field(7:51-7:51):
      K::k_empty_field(7:51-7:51):
```
The synatx tree with source row/col info

If there is any syntax error, you will get:

```shell
Not Parsed content in test.k :
--------------------------------------------------------------------------------
5:*CONTROL_TERMINATION
7:    0 10.0         0       0.0       0.01.000000E8
--------------------------------------------------------------------------------
ROOT(0:0-0:0):
  K::k_title_card(2:1-4:1):
    K::k_title(3:1-3:46):Simple Sphere Impact on Plate - LSDYNA Example
```

## Supported file and version

- [x] LS-DYNA R15(progressing) 

## Build 

Use cmake build project, both work on Linux and Windows. MacOS is not supported yet.

Two ways pull this reposity

1.st way
```shell
git clone --recurse-submodules <this_repo_url>
```
will clone thie repo and with submodules

2.nd way
```shell
git clone <this_repo_url>
# then go to repo dir
git submodule init
git submodule update
```
will clone the repo first, then pull submodules

on Linux
```shell
mkdir build
cd build
cmake ..
make
```

on Windows
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

You will get a application called `parse_file` on build/src/app folder, use `--help` see how to use. Try sample files in sample folder to see how it works.

## Import as library
just include whole project by cmake command
```cmake
add_subdirectory(CAE_input_file_parser)
target_link_libraries(${your_application} PUBLIC caeparser)
```

Most used interface is in `ast.h` and `not_parsed.h`

## Problem andd issue
If you get any output like `Not parsed in file`, you may get involved in two situation.

1.st:
You has some syntax error in your file, as the `Not parsed in file` shows, double check it

2.nd:
We may not supported the syntax yet. Issue me.

You can try enable debug mode to trace parsing process. For application, use `-d/--debug` option. For library, add
```c++
RuntimeConfig::ins()._trace_parser = true;
```
before parse function be called.
