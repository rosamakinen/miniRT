# miniRT
A raytracer implementation in C for rendering realistic 3D scenes, using Minilibx graphics library

<img width="1079" alt="Screen Shot 2023-10-23 at 7 05 12 AM" src="https://github.com/rosamakinen/miniRT/assets/112611789/30b08684-859d-4031-a6c3-04319fe99d41">
scene executed using specular hilights (scenes/multi_object3.rt)



<img width="1082" alt="rt_multi_wide" src="https://github.com/rosamakinen/miniRT/assets/112611789/1e32d3a9-3a2d-41f2-9616-bae63b649a20">
scene executed without specular hilights (scenes/multi_object.rt)

## :star: About

This raytracer project is a simple but educational implementation designed to help you understand the core concepts of ray tracing and 3D rendering. It provides a basic framework for rendering 3D scenes with support lighting, reflections and shading techniques.

## :dizzy: Features

- [x] :rocket: Ray intersection with spheres, cylinders and infinite planes
- [x] :globe_with_meridians: Ambient light with colors 
- [x] :bulb: Diffused light with colors
- [x] :first_quarter_moon: Shadows
- [x] :sparkles: Specular hilights using Blinn-Phong reflection model

## :point_right: Getting Started

To get started with the raytracer:

1. **Clone the repository:**

   ```bash
   git clone https://github.com/rosamakinen/miniRT.git

2. **Cd into the folder**
   ```bash
   cd miniRT
   
3. **Run the program**
   You can run miniRT in two different modes, with or without the specular hilights

   To run the program
   ```bash
   make
   ./miniRT scenes/mapname.rt
   ```

    To run the program with specular hilights run:
     ```bash
     make specular
     ./miniRT scenes/mapname.rt
     ```
<img width="1080" alt="Screen Shot 2023-10-26 at 7 13 36 AM" src="https://github.com/rosamakinen/miniRT/assets/112611789/48f5212c-1061-4969-9bdb-6292da62ef3a">
scene with a cylinder and a plane with only ambient light (scenes/cylinder.rt)



<img width="1078" alt="rt_cylinder" src="https://github.com/rosamakinen/miniRT/assets/112611789/16d30227-c1c5-49df-80fa-b6b8227e1af6">
scene with a cylinder and a plane with ambient light, diffused lighting using one point light and shadows (scene/cylinder.rt)

