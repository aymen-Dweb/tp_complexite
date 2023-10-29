import matplotlib.pyplot as plt

plt.xlabel("Taille de l'arbre")
plt.ylabel("Temps (s)")

# APPEND
xpoints = [10000, 50000, 70000, 80000, 100000]
ypoints = [1.82, 9.51, 14.42, 18.91, 26.43]
plt.plot(xpoints, ypoints,label='REC_PRINTWIDTHORDER')

# INSERT
xpoints = [10000, 50000, 70000, 80000, 100000, 500000, 900000, 1000000]
ypoints = [0, 0, 0.20, 0.39, 0.77, 5.26, 9.52, 13.81]
plt.plot(xpoints, ypoints,label='ITE_PRINTWIDTHORDER')

plt.legend(loc="upper right")

plt.show()