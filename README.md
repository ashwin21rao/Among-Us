## Instructions

Run the following commands:
```
mkdir build
cd build
cmake ..
make
./main
```

## Controls

### Shape Controls

- ```j```, ```l```: translate the shape along global x axis (left, right)
- ```i```, ```k```: translate the shape along global y axis (up, down)
- ```u```, ```o```: translate the shape along global z axis (towards, away)
- ```m```: rotate the shape about a local axis

### Camera Controls

- ```a```, ```d```: translate the camera along camera's x axis (left, right)
- ```w```, ```s```: translate the camera along camera's y axis (up, down)
- ```q```, ```e```: translate the camera along camera's z axis (towards, away)
- ```x```: rotate the camera around the shape
- ```c```: move the camera to a different position

### Other Controls

- ```space```: change shape
- ```1```: toggle rendering mode (fill/wireframe)
- ```esc```: close the window
