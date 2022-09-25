import numpy as np
import matplotlib.pyplot as plt

d = np.loadtxt("data.txt")

fig, ax = plt.subplots()

bins = np.arange(d.min(), d.max(), (d.max() - d.min()) / 100)

ax.hist(d, edgecolor='white', bins=bins)
plt.show()