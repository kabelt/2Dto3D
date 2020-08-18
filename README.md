# 2Dto3D :milky_way:
Want to create your own simple 3D world?
Put in an ASCII map, 2Dto3D will take care of the rest. :metal:
![](images/image2.png)
### Requirements
This project relies on MiniLibX and can be run only on MacOS.
### Installations
run the following command in your terminal
```shell
cd ~/Downloads && git clone https://github.com/kabelt/2Dto3D.git 2Dto3D && cd 2Dto3D && make && ./Cub3D_bonus maps/map1.cub
```
### Controls
| KEY           | Action        |
| ------------- |:-------------:|
| `W`           | move forward  |
| `S`           | move backward |
| `A`           | move to the left     |
| `D`           | move to the right    |
| `→`           | turn right    |
| `←`           | turn left     |
| `M`           | enable/disable minimap|
| `L`           | enable/disable shadow effect|
| `ESC`         | exit      |
### Features
- [x] collision detection
- [x] [sprites](https://en.wikipedia.org/wiki/Sprite_(computer_graphics))
- [x] different wall texturing based on directions
- [x] customizable wall/ceiling colors
- [x] shadow effect based on distance
- [x] minimap
### Acknowledgements
This project is part of 42 pedagogy as Cub3D.
