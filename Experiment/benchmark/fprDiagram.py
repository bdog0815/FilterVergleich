import pandas as pd
import matplotlib.pyplot as plt

# Zusammengefasste Ergebnisse einlesen
df = pd.read_csv("results_summary_explo.csv", sep=";")

# Diagramm erzeugen
plt.figure(figsize=(10, 6))

for filter_name in df["Filter"].unique():
    subset = df[df["Filter"] == filter_name]

    plt.plot(
        subset["Datensatzgroeße"],
        subset["FPR"],
        marker="o",
        label=filter_name
    )

plt.xscale("log")

plt.xlabel("Datensatzgröße")
plt.ylabel("False-Positive-Rate [ns/Element]")
plt.title("False-Positive-Rate in Abhängigkeit der Datensatzgröße")

plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("fpr.png", dpi=300)
plt.show()
