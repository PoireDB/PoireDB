# PoireDB
![](https://img.shields.io/github/license/poiredb/poiredb)
![](https://img.shields.io/tokei/lines/github/poiredb/poiredb)
![](https://img.shields.io/github/workflow/status/poiredb/poiredb/check-pql)
![](https://img.shields.io/github/commit-activity/w/poiredb/poiredb)

PoireDB - is an experimental DBMS made in C.

## Compiling on Windows
You can compile pql with MinGW:
```powershell
cmake -S . -B build/
cd build/
MSBuild.exe pql.sln
```

## On Linux
```bash
cmake -S . -B build/
cd build/
make
```

## License
The project is currently under the [MIT license](https://github.com/PoireDB/PoireDB/blob/master/LICENSE).