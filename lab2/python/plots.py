import numpy as np
import matplotlib.pyplot as plt


# creating the dataset
# data = {'0.1': 1.128571429,
#         '0.25': 1.333333333,
#         '0.50': 2.025,
#         '0.75': 5.111111111,
#         '0.90': 9.090909091}
# courses = list(data.keys())
# values = list(data.values())

#### PLOT1 ####
pdr_data = {
        '0.1': 0.5746536923,
        '0.25': 0.2423636519,
        '0.50': 0.03280416001,
        '0.75': 0.001515151515,
        '0.90': 0
}

pdr_analytical_data = {
        '0.1': 0.59049,
        '0.25': 0.2373046875,
        '0.50': 0.03125,
        '0.75': 0.0009765625,
        '0.90': 0.00001
}

pdr_standard_deviation_data = {
        '0.1': 0.017577595300111,
        '0.25': 0.020337674237231,
        '0.50': 0.0075604936466853,
        '0.75': 0.0030303030304,
        '0.90': 0
}

def plotFunc(data, xLabel, yLabel, color, title):
        
        keys = list(data.keys())
        values = list(data.values())
        
        plot = plt
        plot.bar(keys, values, color=color,
        width=0.4)
        
        plot.xlabel(xLabel)
        plot.ylabel(yLabel)
        plot.title(title)
        # plt.title("Standard deviation for different probabilities")
        plot.grid()
        plot.show()
        
plotFunc(pdr_data, "Loss probability", "PDR", "maroon", "PDR simulation")
plotFunc(pdr_analytical_data, "Loss probability", "PDR", "blue", "PDR analytical")
plotFunc(pdr_standard_deviation_data, "Loss probability", "Standard deviation", "purple", "PDR Standard deviation")

# plt.show()