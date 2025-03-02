import matplotlib.pyplot as plt
import matplotlib as mpl
import csv
import numpy as np

# Set global font to Times New Roman
mpl.rcParams['font.family'] = 'Times New Roman'
mpl.rcParams['mathtext.fontset'] = 'cm'  # Ensures LaTeX math uses Times New Roman

def create_plot(file):
    n_values = []
    weights = []
    t_values = []

    with open(file, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            n_values.append(float(row[0]))
            weights.append(float(row[1]))
            t_values.append(float(row[2]))

    # Convert to NumPy arrays for fitting
    n_values = np.array(n_values)
    weights = np.array(weights)

    # Transform data for a power-law fit (assume f(n) = a * n^b)
    log_n = np.log(n_values)
    log_weights = np.log(weights)

    # Perform linear regression on log-transformed data (log(y) = log(a) + b * log(n))
    coeffs = np.polyfit(log_n, log_weights, 1)  # Return [b, log(a)]
    b, log_a = coeffs
    a = np.exp(log_a)  # Convert log(a) back to a

    # Generate smooth values for plotting best-fit curve
    x_smooth = np.linspace(min(n_values), max(n_values), 200)
    y_smooth = a * x_smooth**b  # Power-law best fit function


    # Plot best-fit curve and discrete data points
    plt.plot(x_smooth, y_smooth, 'r-', linewidth=1, label=rf"$f(n) = {a:.3f} n^{{{b:.3f}}}$", zorder=1)
    plt.scatter(n_values, weights, color='blue', s=20, zorder=2)

    plt.xlabel(r"$n$ (number of vertices)")
    plt.ylabel("Average MST Weight")
    plt.title("n vs. Average MST Weight")
    plt.grid(True)
    plt.legend()
    plt.show()

def main():
    csv_file = "final_results(d=0).csv" # Change file name manually
    create_plot(csv_file)

if __name__ == "__main__":
    main()