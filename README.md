# R-type
R-type like engine/game

To build R-type run

_Linux_
```bash
rm -rf build && mkdir -p build && cd build && cmake .. && make && cd .. && ls ./r-type
```
_Windows_
```batch
rd /s /q build & md build && cd build && cmake .. && cmake --build . && cd Debug/ && dir r-type.exe
```
