import numpy as np
import matplotlib.pyplot as plt

def rotation_matrix(theta):
    theta_rad = np.radians(theta)
    return np.array([
        [np.cos(theta_rad), -np.sin(theta_rad), 0],
        [np.sin(theta_rad), np.cos(theta_rad), 0],
        [0, 0, 1]
    ])

def rotate_point(point, theta):
    R = rotation_matrix(theta)
    point_homogeneous = np.array([point[0], point[1], 1])
    rotated_point = np.dot(R, point_homogeneous)
    return rotated_point[:2]  # Returns only x, y

def rotate_triangle(vertices, theta):
    return np.array([rotate_point(vertex, theta) for vertex in vertices])



# Definizione del triangolo (vertici)a
triangle = np.array([
    [1, 0],  # Vertice A
    [2, 0],  # Vertice B
    [1.5, 1]  # Vertice C
])

angle = -30  # gradi

# Rotazione del triangolo
rotated_triangle = rotate_triangle(triangle, angle)

# Plotting
plt.figure(figsize=(6, 6))
plt.axhline(0, color='gray', lw=0.5, ls='--')
plt.axvline(0, color='gray', lw=0.5, ls='--')

# Disegno del triangolo originale
plt.fill(*zip(*triangle), color='blue', alpha=0.5, label='Original Triangle')

# Disegno del triangolo ruotato
plt.fill(*zip(*rotated_triangle), color='red', alpha=0.5, label=f'Rotated Triangle by {angle}°')

plt.xlim(-2, 2)
plt.ylim(-2, 2)
plt.grid()
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Triangle Rotation')
plt.legend()
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
