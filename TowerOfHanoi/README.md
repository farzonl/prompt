# Tower of Hanoi

### Example
![](pics/example.svg?sanitize=true)

### Usage
```bash
./TowerOfHanoi
./TowerOfHanoi <integer| # of disks>
./TowerOfHanoi <integer| # of disks> -print_state
./TowerOfHanoi -h
```
### Build Docs
- #### Requirments
        - Doxygen
        - Graphviz
```bash
    cd TowerOfHanoi
    doxygen
```


### Build with Ninja
```bash
cmake -G Ninja -B build
ninja -C./build
```

### Building on Windows 
- Using Ninja
```powershell
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release
ninja -C./build
```
- Using MSBUILD
```powershell
cmake -B build
msbuild build\TowerOfHanoi.sln -t:Build -p:Configuration=Release
```

## Supported Platform(s)
- OS X
- Linux
- Windows

