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

# First translation
t_x1 = 5
t_y1 = 4
T1 = translation_matrix(t_x1, t_y1)
print("Translation Matrix T1:")
print(T1)

# Second translation
t_x2 = 3
t_y2 = 2
T2 = translation_matrix(t_x2, t_y2)
print("\nTranslation Matrix T2:")
print(T2)

# Combine the two translation matrices
T_combined = np.dot(T2, T1)
print("\nCombined Translation Matrix T_combined:")
print(T_combined)

# Translate the original point using the combined translation matrix
translated_point = translate_point(point, T_combined)
print(f"\nOriginal point: {point}")
print(f"Translated point using combined matrix: {translated_point}")

# Inverse of the combined translation matrix
T_combined_inv = np.linalg.inv(T_combined)
print("\nInverse of the Combined Translation Matrix:")
print(T_combined_inv)

# Translate back to the original point
translated_back_point = translate_point(translated_point, T_combined_inv)
print(f"Point after inverse translation: {translated_back_point}")
