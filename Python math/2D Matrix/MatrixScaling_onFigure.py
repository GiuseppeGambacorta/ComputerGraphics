import numpy as np
import matplotlib.pyplot as plt

printed_s = False

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

def scaling_matrix(sx, sy):
    return np.array([
        [sx, 0, 0],
        [0, sy, 0],
        [0, 0, 1]
    ])

def scale_point(point, sx, sy):
    global printed_s  # Usare la variabile globale
    
    S = scaling_matrix(sx, sy)
    
    # Stampa S solo la prima volta che viene chiamata la funzione
    if not printed_s:
        print("Scaling Matrix S:\n", S)
        print("inverted S:\n" ,np.linalg.inv(S))
        printed_s = True  # Aggiorna la variabile per evitare future stampe

    point_homogeneous = np.array([point[0], point[1], 1])
    scaled_point = np.dot(S, point_homogeneous)
    return scaled_point[:2]  # Returns only x, y

def scale_triangle(vertices, sx, sy):
    # Calculate centroid
    centroid = np.mean(vertices, axis=0)
    
    # Translate to origin using -centroid
    T = translation_matrix(-centroid[0], -centroid[1])
    translated_vertices = np.array([translate_point(vertex, T) for vertex in vertices])

    # Scale the triangle
    scaled_vertices = np.array([scale_point(vertex, sx, sy) for vertex in translated_vertices])

    # Inverse translation to original position using T^-1
    inverse_T = np.linalg.inv(T)  
    
    return np.array([translate_point(vertex, inverse_T) for vertex in scaled_vertices])

# Definition of the triangle (vertices)
triangle = np.array([
    [0, 0],  # Vertex A
    [1, 0],  # Vertex B
    [0.5, 1]  # Vertex C
])

scaling_factor_x = 0.5  # Scale factor for x-axis
scaling_factor_y = 0.5  # Scale factor for y-axis

# Scaling the triangle
scaled_triangle = scale_triangle(triangle, scaling_factor_x, scaling_factor_y)

# Plotting
plt.figure(figsize=(6, 6))
plt.axhline(0, color='gray', lw=0.5, ls='--')
plt.axvline(0, color='gray', lw=0.5, ls='--')

# Drawing the original triangle
plt.fill(*zip(*triangle), color='blue', alpha=0.5, label='Original Triangle')

# Drawing the scaled triangle
plt.fill(*zip(*scaled_triangle), color='red', alpha=0.5, label='Scaled Triangle')

plt.xlim(-1, 2)
plt.ylim(-1, 2)
plt.grid()
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Triangle Scaling Around Centroid with Translation')
plt.legend()
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
