import numpy as np

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

# Example usage
point = (2, 3)
t_x = 5
t_y = 4
T = translation_matrix(t_x, t_y)
print(T)
translated_point = translate_point(point, T)
print(f"Original point: {point}")
print(f"Translated point: {translated_point}")

# Inverse translation
T = np.linalg.inv(T)
print(T)

# Translate back to the original point
translated_back_point = translate_point(translated_point, T)
print(f"Point after inverse translation: {translated_back_point}")
