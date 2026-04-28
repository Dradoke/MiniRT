# MiniRT

MiniRT is a Raytracing rendering engine (based on the 42 MiniRT project) developed in C using the MLX42 library. This project allows for the visualization of complex 3D scenes defined in configuration files, using ray tracing techniques to simulate light and materials.

## 🚀 Features

### Geometric Shapes
The engine supports rendering of the following primitives:
- **Spheres** (sp)
- **Planes** (pl)
- **Cylinders** (cy)
- **Triangles** (tr)
- **3D Meshes**

### Lighting and Rendering
- **Ambient Light**: Global scene illumination.
- **Point Lights**: Light sources positioned in space.
- **Path Tracing**: Realistic rendering simulating physical light behavior (can be activated for high-quality output).
- **Real-time Rendering**: Fluid navigation with adaptive resolution during movement.

### Visual Effects
- **Reflections**: Simulation of reflective surfaces.
- **Fisheye**: Wide-angle optical distortion effect.

## 🛠 Installation

To compile the project, you need `make` and a C compiler (like `cc` or `gcc`). The project uses MLX42.

1. Clone the repository:
   ```bash
   git clone https://github.com/Dradoke/SkibidiRT.git
   cd SkibidiRT
   ```

2. Compile the project:
   ```bash
   make
   ```

This will generate the `miniRT` executable.

## 🎮 Usage

To launch the program, provide a `.rt` scene file as an argument:

```bash
./miniRT scenes/beach.rt
```

You can find several example scenes in the `scene/` folder:
- `banana.rt`
- `beach.rt`
- `demo.rt`
- `hawk.rt`
- `house.rt`
- `m9.rt`
- `sword.rt`

## ⌨️ Controls

The interface allows you to navigate the scene and modify rendering parameters in real-time.

### Movement and Camera

| Key / Action | Description |
| :--- | :--- |
| **W** | Move Forward |
| **S** | Move Backward |
| **A** | Strafe Left (Standing Mode) / Roll Left (Plane Mode) |
| **D** | Strafe Right (Standing Mode) / Roll Right (Plane Mode) |
| **Right Click (Hold)** | Rotate Camera (Look around) |
| **C** | Toggle Camera Mode (Standing ↔ Plane) |

### Rendering and Options

| Key | Description |
| :--- | :--- |
| **E** | Start High Quality Render (Full Path Tracing) |
| **P** | Toggle Fisheye Effect |
| **R** | Toggle Reflections |
| **ESC** | Quit the program |

## 📝 Scene Format (.rt)

The `.rt` files describe the scene elements. Each line starts with a type identifier followed by its properties.

### Object Configuration

#### Ambient Light (A)
```
A [ratio] [color]
```
- **ratio**: Ambient lighting ratio in range `[0.0, 1.0]`.
- **color**: R,G,B colors in range `[0-255]`.

#### Camera (C)
```
C [view_point] [orientation] [FOV]
```
- **view_point**: x,y,z coordinates of the view point.
- **orientation**: 3D normalized orientation vector. In range `[-1.0, 1.0]` for each axis.
- **FOV**: Horizontal field of view in degrees in range `[0-180]`.

#### Light (L)
```
L [light_point] [brightness] [color]
```
- **light_point**: x,y,z coordinates of the light point.
- **brightness**: Light brightness ratio in range `[0.0, 1.0]`.
- **color**: R,G,B colors in range `[0-255]`.

#### Sphere (sp)
```
sp [center] [diameter] [color]
```
- **center**: x,y,z coordinates of the sphere center.
- **diameter**: The sphere diameter.
- **color**: R,G,B colors in range `[0-255]`.

#### Plane (pl)
```
pl [point] [normal] [color]
```
- **point**: x,y,z coordinates of a point in the plane.
- **normal**: 3D normalized normal vector. In range `[-1.0, 1.0]` for each axis.
- **color**: R,G,B colors in range `[0-255]`.

#### Cylinder (cy)
```
cy [center] [axis] [diameter] [height] [color]
```
- **center**: x,y,z coordinates of the center of the cylinder.
- **axis**: 3D normalized vector of axis of cylinder. In range `[-1.0, 1.0]` for each axis.
- **diameter**: The cylinder diameter.
- **height**: The cylinder height.
- **color**: R,G,B colors in range `[0-255]`.

#### Triangle (tr)
```
tr [p1] [p2] [p3] [color]
```
- **p1**: x,y,z coordinates of the first vertex.
- **p2**: x,y,z coordinates of the second vertex.
- **p3**: x,y,z coordinates of the third vertex.
- **color**: R,G,B colors in range `[0-255]`.

### Example
```
A   0.2             255,255,255
C   0,0,-10         0,0,1           70
L   -40,0,30        0.7             255,255,255
sp  0,0,20          20              255,0,0
pl  0,-10,0         0,1,0           0,0,225
```
