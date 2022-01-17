<p align="center"><img width="100" src="./images/poiredb_icon.svg"></img></p>
<h1 align="center"><a href="https://github.com/poiredb/poiredb">PoireDB - fast and easy Database Control System</a></h1>

<p align="center">
<img src="https://github.com/poiredb/poiredb/workflows/Windows/badge.svg"></img>
<img src="https://github.com/poiredb/poiredb/workflows/Ubuntu/badge.svg"></img>
<img src="https://github.com/poiredb/poiredb/workflows/MacOS/badge.svg"></img>
<img src="https://img.shields.io/github/license/poiredb/poiredb"></img>
<img src="https://img.shields.io/tokei/lines/github/poiredb/poiredb"></img>
<img src="https://img.shields.io/github/commit-activity/w/poiredb/poiredb"></img>
</p>

<p align="center"><img width="600" src="images/carbon.png"></img></p>

## Compiling on Windows

### Compiling PQL
Requirements: `Visual Studio, MSBuild, CMake, Golang`
```powershell
cd pql/
cmake -S . -B build/
cd build/
MSBuild.exe pql.sln
```
Then add all binaries into the `$PATH` environmental variable.

### Compiling PoireDB server
```powershell
cd ../..
go build cmd/poiredb
```

## On Linux
### Compiling PQL
Requirements: `Makefile, CMake, GCC`
```bash
cd pql/
cmake -S . -B build/
cd build/
make
```

Then for all binaries do:
```bash
sudo cp <binary> $HOME/bin/<binary>
```

### Compiling PoireDB server
Requirements: `Golang`
```bash
cd ../..
go build cmd/poiredb
```

## License
The project is currently under the [MIT license](https://github.com/PoireDB/PoireDB/blob/master/LICENSE).

## Documentation
All documentation can be found [here](https://github.com/PoireDB/PoireDB/wiki).