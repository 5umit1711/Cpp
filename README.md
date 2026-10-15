# SDL2 Physics Simulations

This repository contains two small C++ simulations using SDL2:

- `Bouncy_Ball.cpp` — a ball bouncing inside a window under gravity.
- `Gravity.cpp` — an earth-like body orbiting a black hole.

## Requirements

- Windows
- Git
- MinGW GCC (`g++`)

SDL2's headers, import library, and runtime DLL are included in this repository, so you do not need to install SDL2 separately. Use a MinGW compiler whose target architecture matches the included SDL2 library and `SDL2.dll`.

## Download

Open Git Bash and run:

```bash
git clone https://github.com/5umit1711/Cpp.git
cd Cpp
```

If `g++` is not recognized, install MinGW GCC and make sure its `bin` directory is on your `PATH`. Verify it is available with:

```bash
g++ --version
```

## Build and run

Run these commands from the repository directory in Git Bash. Build either simulation:

```bash
g++ -std=c++17 Bouncy_Ball.cpp -I./inc -L./lib -lSDL2 -o Bouncy_Ball.exe
./Bouncy_Ball.exe
```

```bash
g++ -std=c++17 Gravity.cpp -I./inc -L./lib -lSDL2 -o Gravity.exe
./Gravity.exe
```

In PowerShell, use `.\Bouncy_Ball.exe` or `.\Gravity.exe` to launch the corresponding program. Keep `SDL2.dll` in the repository directory beside the generated executable.

Close the simulation window to exit.

## Physics used

### Bouncing ball

Each frame updates the ball's position and vertical velocity using a simple discrete approximation:

```text
x = x + vx
y = y + vy
vy = vy + g
```

On contact with a window edge, the relevant velocity component is reversed and multiplied by `0.5`, modeling energy loss on impact.

### Two-body gravity

The simulation calculates the gravitational force magnitude and acceleration:

```text
F = G * M * m / r^2
a = F / m
```

It then updates velocity and position using the time step `dt`:

```text
v = v + a * dt
position = position + v * dt
```

These are simplified, discrete simulations; the constants are chosen for visualization and are not intended as real-world units.
