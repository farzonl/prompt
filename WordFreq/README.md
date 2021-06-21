# Word Frequency
### Example
![](pics/example.svg?sanitize=true)

### Usage
```bash
./WordFreq [...<string| filepath>]
./WordFreq -l [...<string| filepath>]
./WordFreq -h
```
#### Flags
- l creates a frequency file per input.
- h this is a help flag


### Build Docs
- #### Requirments
        - Doxygen
        - Graphviz
```bash
    cd WordFreq
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
msbuild build\WordFreq.sln -t:Build -p:Configuration=Release
```

## Docker Build & Run
- build: `docker build -t word_freq:latest .`
- run: `docker run  --name word_freq_vm -it word_freq:latest`

## Supported Platform(s)
- OS X
- Linux
- Windows

