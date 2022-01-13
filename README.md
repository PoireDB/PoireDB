<p align="center"><img width="100" src="https://avatars.githubusercontent.com/u/97557785?s=400&u=dcd5c22a819e9ea281aff71005524ffa181ae7f0&v=4"></img></p>
<h1 align="center"> PoireDB </h1>

![](https://github.com/poiredb/poiredb/workflows/Windows/badge.svg)
![](https://github.com/poiredb/poiredb/workflows/Ubuntu/badge.svg)
![](https://github.com/poiredb/poiredb/workflows/MacOS/badge.svg)
![](https://img.shields.io/github/license/poiredb/poiredb)
![](https://img.shields.io/tokei/lines/github/poiredb/poiredb)
![](https://img.shields.io/github/commit-activity/w/poiredb/poiredb)

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