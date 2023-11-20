import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import fsolve

# Define the function
def g(x):
    return 0.25 * x**3 + x - 1.2502

# Generate x values
x_values_g = np.linspace(-2, 2, 400)

# Generate y values
y_values_g = g(x_values_g)

# Find roots using fsolve
roots_g = fsolve(g, [-3, -2, -1, 2])

# Plot the function
plt.figure(figsize=(8, 6))
plt.plot(x_values_g, y_values_g, label='$g(x) = 0.25x^3 + x - 1.2502$')

# Mark roots on the plot
plt.scatter(roots_g, [0] * len(roots_g), color='red', label='Roots')

# Customize the plot
plt.title('График функции 2 с корнями')
plt.xlabel('x')
plt.ylabel('g(x)')
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.legend()
plt.grid(True)

# Show the plot
plt.show()
