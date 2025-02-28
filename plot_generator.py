import matplotlib.pyplot as plt
import csv

def create_plot(file):
    n_values = []
    weights = []

    with open(file, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            n_values.append(float(row[0]))
            weights.append(float(row[1]))

    plt.plot(n_values, weights, marker='o', linestyle='-')
    plt.xlabel("Number of Vertices (n)")
    plt.ylabel("Average MST Weight")
    plt.title("n vs. Average MST Weight")
    plt.grid(True)
    plt.show()

def main():
    csv_file = "final_results.csv"
    create_plot(csv_file)

if __name__ == "__main__":
    main()