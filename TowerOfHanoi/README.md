# Tower of Hanoi

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
