import numpy as np

# Definition of the matrices
M = np.array([
    [1, 0, 0],
    [0, 1, 0],
    [4, 4, 1]
])

def transform_F_to_F2(point):
    if len(point) == 2:
        point = np.array([point[0], point[1], 1])
    result = np.dot(M, point)
    return result[:2]  # Returns only x, y

def transform_F2_to_F(point):
    if len(point) == 2:
        point = np.array([point[0], point[1], 1])
    result = np.dot(M_t, point)
    return result[:2]  # Returns only x, y

print("M:")
print(M)

M_t = M.T 
M = np.linalg.inv(M_t) 

print("\nTranspose of M (M_t):")
print(M_t)
print("\nInverse of the transpose of M (M_inverse):")
print(M)

# Test the transformations
point_F2 = (2, 2)
print(f"Point in F2: {point_F2}")

point_F1 = transform_F2_to_F(point_F2)
print(f"Point in F1: {point_F1}")

point_F2 = transform_F_to_F2(point_F1)
print(f"Point in F2: {point_F2}")
