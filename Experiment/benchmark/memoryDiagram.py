import pandas as pd
import matplotlib.pyplot as plt

# Zusammengefasste Ergebnisse einlesen
df = pd.read_csv("results_summary.csv", sep=";")

# Diagramm erzeugen
plt.figure(figsize=(10, 6))

for filter_name in df["Filter"].unique():
    subset = df[df["Filter"] == filter_name]

    plt.plot(
        subset["Datensatzgroeße"],
        subset["SpeicherProElement"],
        marker="o",
        label=filter_name
    )

plt.xscale("linear")

plt.xlabel("Datensatzgröße")
plt.ylabel("Speicherbedarf [Bit/Element]")
plt.title("Speicherbedarf in Abhängigkeit der Datensatzgröße")

plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("memory.png", dpi=300)
plt.show()
