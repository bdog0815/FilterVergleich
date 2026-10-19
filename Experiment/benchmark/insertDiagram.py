import pandas as pd
import matplotlib.pyplot as plt

# Zusammengefasste Ergebnisse einlesen
df = pd.read_csv("results/results_summary.csv", sep=";")

# Diagramm erzeugen
plt.figure(figsize=(10, 6))

for filter_name in df["Filter"].unique():
    subset = df[df["Filter"] == filter_name]

    plt.plot(
        subset["Datensatzgroeße"],
        subset["Einfuegezeit"],
        marker="o",
        label=filter_name
    )

plt.xscale("linear")

plt.xlabel("Datensatzgröße")
plt.ylabel("Einfüge-Zeit [ns]")

plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("insert_time.png", dpi=300)
plt.show()
