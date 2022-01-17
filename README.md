<p align="center"><img width="100" src="./poiredb_icon.svg"></img></p>
<h1 align="center"> PoireDB </h1>

<p align="center">

![](https://github.com/poiredb/poiredb/workflows/Windows/badge.svg)
![](https://github.com/poiredb/poiredb/workflows/Ubuntu/badge.svg)
![](https://github.com/poiredb/poiredb/workflows/MacOS/badge.svg)
![](https://img.shields.io/github/license/poiredb/poiredb)
![](https://img.shields.io/tokei/lines/github/poiredb/poiredb)
![](https://img.shields.io/github/commit-activity/w/poiredb/poiredb)

</p>
  
PoireDB - is an experimental DBMS made in C.

## Compiling on Windows
Requirements: `Visual Studio, MSBuild, CMake`
```powershell
cmake -S . -B build/
cd build/
MSBuild.exe pql.sln
```

## On Linux
Requirements: `Makefile, CMake, GCC`
```bash
cmake -S . -B build/
cd build/
make
```

## License
The project is currently under the [MIT license](https://github.com/PoireDB/PoireDB/blob/master/LICENSE).
