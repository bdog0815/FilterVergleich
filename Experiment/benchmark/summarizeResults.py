import pandas as pd
import glob

# Alle Ergebnisdateien laden
files = glob.glob("results/results_*.csv")

tables = []

for file in files:
    df = pd.read_csv(file, sep=";")
    tables.append(df)

data = pd.concat(tables, ignore_index=True)

# Mittelwerte bilden
summary = (
    data.groupby(["Datensatzgroeße", "Filter"])
    .agg({
        "SpeicherBytes": "mean",
        "SpeicherProElement": "mean",
        "Einfuegezeit": "mean",
        "Konstruktionszeit": "mean",
        "positiveLookups": "mean",
        "negativeLookups": "mean",
        "Loeschzeit": "mean",
        "FPR": "mean"
    })
    .reset_index()
)

summary.to_csv(
    "results_summary.csv",
    sep=";",
    index=False
)

print(summary)
