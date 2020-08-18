# 2Dto3D :milky_way:
Want to create your own simple 3D world?
Put in an ASCII map, 2Dto3D will take care of the rest. :metal:
All of the features were implemented without the any help from external libraries. :star:
![](images/image2.png)
### Requirements
This project relies on MiniLibX and can be run only on MacOS.
### Installations
run the following command in your terminal. You should see the window similar to the above screenshot.
```shell
cd ~/Downloads && git clone https://github.com/kabelt/2Dto3D.git 2Dto3D && cd 2Dto3D && make && ./2Dto3D maps/map1.cub
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
### It's time to create you own world!
You can find the details about how .cub files works [here](subject/en.subject.pdf) on page 6-9.
Then relaunch 2Dto3D with your map;
```shell
./2Dto3D <your_map>
```
### Acknowledgements
This project is part of 42 pedagogy originally as Cub3D.
