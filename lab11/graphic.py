import matplotlib.pyplot as plt
import numpy as np

arr = np.loadtxt('/Users/danilapecenin/Library/Mobile Documents/com~apple~CloudDocs/Documents/XCode Projects/lab11/lab11/results.txt')
print("Поулченный массив из программы на C:")
print(arr)

amount_of_data = arr[:7]
tree_time = arr[7:14]
hash_time = arr[14:22]

print(f"Количество данных {amount_of_data}")
print(f"Время работы поиска с помощью бинарного дерева: {tree_time}")
print(f"Время работы поиска с помощью хэш-таблицы дерева: {hash_time}")

plt.plot(amount_of_data, tree_time, color='green', label='Бинарное дерево')
plt.plot(amount_of_data, hash_time, color='red', label='Хэш-таблица')
plt.xlabel('Количество данных для поиска, шт.')
plt.ylabel('Время поиска, с.')
plt.grid(True)
plt.legend()
plt.show()
