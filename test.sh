#!/bin/bash

total=0
runs=10

for i in $(seq 1 $runs); do
    echo "Run $i..."

    # Capture uniquement le temps réel en secondes
    t=$(/usr/bin/time -f "%e" ./hotrace < massive_test.htr 2>&1 >/dev/null)

    echo "Temps: $t s"

    # Addition avec bc pour gérer les décimales
    total=$(echo "$total + $t" | bc)
done

# Calcul de la moyenne
average=$(echo "scale=4; $total / $runs" | bc)

echo "----------------------"
echo "Temps total: $total s"
echo "Moyenne sur $runs runs: $average s"