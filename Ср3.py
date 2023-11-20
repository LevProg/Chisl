import matplotlib.pyplot as plt
import numpy as np
# Чтение значений из файла
with open('C:/Users/Aser/source/repos/ChisMethods/result2.txt', 'r') as file:
    lines1 = file.readlines()
# Чтение значений из файла
with open('C:/Users/Aser/source/repos/ChisMethods/result3.txt', 'r') as file:
    lines2 = file.readlines()
# Преобразование строк в числа
values1 = [float(line.strip()) for line in lines1]
values2 = [float(line.strip()) for line in lines2]

x_values = np.linspace(-10, 8, 100)
y_values = x_values


# Создание списка номеров строк (x)
line_numbers = list(10**x for x in range(-15, len(values1)-15))
print(values1)
print(values2)
print(line_numbers)
# Построение графика
plt.figure(figsize=(8, 6))
plt.semilogx()
plt.semilogy()
plt.plot(x_values, y_values, color='g',label='y=x')
plt.plot(line_numbers, values1, linestyle='-', color='b',label='Bisection method')
plt.plot(line_numbers, values2, linestyle='-', color='r',label='Hord method')
# Настройка графика
plt.title('f(x)=(x^4 + 3*x^3 - 9*x - 9)/(x - 1)')
plt.xlabel('Eps')
plt.ylabel('Loss')

plt.xlim(0,0.01)  # Установите желаемый диапазон по оси x
plt.ylim(0,0.01)  # Установите желаемый диапазон по оси y
plt.legend()
plt.grid(True)

# Показать график
plt.show()
