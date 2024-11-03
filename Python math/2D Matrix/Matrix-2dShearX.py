import numpy as np
import matplotlib.pyplot as plt

def shear_matrix(shear_factor):
    return np.array([
        [1, shear_factor, 0],  # Shear in the x direction
        [0, 1, 0],              # No shear in the y direction
        [0, 0, 1]               # Homogeneous coordinate
    ])

def shear_point(point, S):
    point_homogeneous = np.array([point[0], point[1], 1])
    sheared_point = np.dot(S, point_homogeneous)
    return sheared_point[:2]  # Returns only x, y

def shear_shape(vertices, shear_factor):
    S = shear_matrix(shear_factor)
    return np.array([shear_point(vertex, S) for vertex in vertices])

# Define the square vertices
square = np.array([
    [0, 0],  # Bottom-left
    [1, 0],  # Bottom-right
    [1, 1],  # Top-right
    [0, 1],  # Top-left
    [0, 0]   # Closing the square
])

# Shear factor
shear_factor = 1.0  # Amount of shear to apply

# Shear the square
sheared_square = shear_shape(square, shear_factor)

# Plotting
plt.figure(figsize=(6, 6))
plt.axhline(0, color='gray', lw=0.5, ls='--')
plt.axvline(0, color='gray', lw=0.5, ls='--')

# Draw the original square
plt.fill(*zip(*square), color='blue', alpha=0.5, label='Original Square')

# Draw the sheared square
plt.fill(*zip(*sheared_square), color='red', alpha=0.5, label='Sheared Square')

plt.xlim(-1, 3)
plt.ylim(-1, 2)
plt.grid()
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Square Shear Transformation')
plt.legend()
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
