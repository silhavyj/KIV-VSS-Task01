# KIV/VSS - Task 01

## Requirements

The application is written in C++. To run this program, the user is expected to have `cmake` and `make` (`mingw32-make` in case of Windows) installed on their machine. They also need to have both tools added to the `PATH`.

## Compilation & Run

If all requirements are met, the user can use prepared scripts to build and run the application.

### Windows

```
run.bat <filename>
```

### Linux

```
./run.sh <filename>
```
The `filename` is the path to the input file as required by the assignment.

## Demo

### `data.dat`

```
1 0.25
6 0.10
8 0.40
10 0.15
15 0.10
```

```
./run.sh data.dat
```

```
E_teorie=7.05
D_teorie=17.2475
E_vypocet=7.04473
D_vypocet=17.1877

1:*******************************
6:************
8:**************************************************
10:******************
15:************
```