import numpy as np
import matplotlib.pyplot as plt


def translation_matrix(t_x, t_y):
    return np.array([
        [1, 0, t_x],
        [0, 1, t_y],
        [0, 0, 1]
    ])

def translate_point(point, T):
    point_homogeneous = np.array([point[0], point[1], 1])
    translated_point = np.dot(T, point_homogeneous)
    return translated_point[:2]  # Returns only x, y

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
    # Calculate centroid
    centroid = np.mean(vertices, axis=0)
    
    # Translate to origin using -centroid
    T = translation_matrix(-centroid[0], -centroid[1])
    translated_vertices = np.array([translate_point(vertex, T) for vertex in vertices])

    # Rotate the triangle
    rotated_vertices = np.array([rotate_point(vertex, theta) for vertex in translated_vertices])

    # Inverse translation to original position using centroid
    inverse_T = translation_matrix(centroid[0], centroid[1])  # Inverse translation
    return np.array([translate_point(vertex, inverse_T) for vertex in rotated_vertices])

# Define the triangle (vertices)
triangle = np.array([
    [1, 0],  # Vertex A
    [2, 0],  # Vertex B
    [1.5, 1]  # Vertex C
])

angle = -30  # degrees

# Rotate the triangle around its centroid
rotated_triangle = rotate_triangle(triangle, angle)

# Plotting
plt.figure(figsize=(6, 6))
plt.axhline(0, color='gray', lw=0.5, ls='--')
plt.axvline(0, color='gray', lw=0.5, ls='--')

# Draw the original triangle
plt.fill(*zip(*triangle), color='blue', alpha=0.5, label='Original Triangle')

# Draw the rotated triangle
plt.fill(*zip(*rotated_triangle), color='red', alpha=0.5, label=f'Rotated Triangle by {angle}°')

plt.xlim(-1, 3)
plt.ylim(-1, 2)
plt.grid()
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Triangle Rotation Around Centroid')
plt.legend()
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
