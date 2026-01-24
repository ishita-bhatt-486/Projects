# 2D Python Physics Engine

An interactive 2D physics simulation built using Python and Pygame. This engine simulates gravity, friction, wall collisions, and complex elastic collisions between balls of varying masses and sizes.

## Features

* **Realistic Physics:** Implements gravity, air resistance, and energy losses on impact.
* **Energy conservation:** accurate momentum conservation and collision resolution between balls of different sizes/masses using vector math.
* **Interactive Controls:**
    * **Add Balls:** Click a button to add balls with random sizes and masses.
    * **Drag & Throw:** Click and drag existing balls to interact with them physically and to simulate collisions. Throwing them imparts velocity based on mouse movement and simulates real world physics.

## Setup

### Prerequisites
1. Requires python to be installed
2.  **Install Pygame:**
    ```bash
    pip install pygame
    ```

## Controls

| Action | Input |
| :--- | :--- |
| **Add Ball** | Click the **"Add Ball"** button in the top-left corner. |
| **Grab Ball** | **Left-Click** and hold on any ball. |
| **Throw Ball** | Drag the mouse while holding a ball and release to "throw" it. |
| **Exit** | Click the **X** on the window to close. |

## Configuration
To tweak the behavior of the simulation, modify the constants at the top of the Python script:

```python
GRAVITY = 0.5           # Changes the downward acceleration per frame
FRICTION = 0.99         # Adjust the air resistance (1.0 = no friction, <1.0 = slows down)
WALL_ELASTICITY = 0.8   # Adjust bounciness of walls (0.0 = stick, 1.0 = perfect bounce)
COLLISION_DAMPING = 0.9 # Energy lost when two balls hit each other