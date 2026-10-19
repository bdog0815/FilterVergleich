import pandas as pd
import matplotlib.pyplot as plt

# Daten laden
df = pd.read_csv("results/results_summary.csv", sep=";")

plt.figure(figsize=(10, 6))

# Nur die beiden gewünschten Filter
filter_colors = {
    "Cuckoo12-2^n": "green",
    "CountingBloom10-addAll": "orange"
}

for filter_name, color in filter_colors.items():
    subset = df[df["Filter"] == filter_name]

    plt.plot(
        subset["Datensatzgroeße"],
        subset["Loeschzeit"],
        marker="o",
        color=color,
        linewidth=2,
        label=filter_name
    )

plt.xscale("linear")

plt.xlabel("Datensatzgröße")
plt.ylabel("Löschzeit [ns]")

plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("delete_time.png", dpi=300)
plt.show()
