import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results_summary_explo.csv", sep=";")

colors = {
    "Xor8": "red",
    "Cuckoo12-2^n": "green",
    "Bloom12-addAll": "blue",
    "CountingBloom10-addAll": "orange"
}

plt.figure(figsize=(10, 6))

for filter_name in df["Filter"].unique():
    subset = df[df["Filter"] == filter_name]

    # Positive Lookups
    plt.plot(
        subset["Datensatzgroeße"],
        subset["positiveLookups"],
        color=colors[filter_name],
        linestyle="-",
        marker="o",
        label=f"{filter_name} (+)"
    )

    # Negative Lookups
    plt.plot(
        subset["Datensatzgroeße"],
        subset["negativeLookups"],
        color=colors[filter_name],
        linestyle="--",
        marker="x",
        label=f"{filter_name} (-)"
    )

plt.xscale("log")

plt.xlabel("Datensatzgröße")
plt.ylabel("Anfrage-Zeit [ns]")
plt.title("Positive und negative Anfrage-Zeiten")

plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("lookup_times.png", dpi=300)
plt.show()
