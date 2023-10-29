import matplotlib.pyplot as plt

plt.xlabel("Taille de la chaine")
plt.ylabel("Temps (ms)")


# APPEND
xpoints = [50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
ypoints = [0, 0, 0, 0, 1, 1, 2, 2, 2, 3, 4]
plt.plot(xpoints, ypoints,label='RANGE_APPEND')

# INSERT
xpoints = [50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
ypoints = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
plt.plot(xpoints, ypoints,label='RANGE_INSERT')

plt.legend(loc="upper left")

plt.show()