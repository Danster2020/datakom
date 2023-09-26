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

data = {'0.1': 0.37498299281162,
        '0.25': 0.54433105395182,
        '0.50': 1.1508149286484,
        '0.75': 3.0892086165462,
        '0.90': 6.7082039324994}
courses = list(data.keys())
values = list(data.values())

fig = plt.figure(figsize=(10, 5))

# creating the bar plot
plt.bar(courses, values, color='maroon',
        width=0.4)

# plt.xlabel("Probabilities")
# plt.ylabel("Average nr of attempts")
# plt.title("Average nr of attempts for different probabilities")
# plt.show()

plt.xlabel("Probabilities")
plt.ylabel("Standard deviation")
plt.title("Standard deviation for different probabilities")
plt.show()