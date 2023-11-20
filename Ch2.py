import matplotlib.pyplot as plt

# Чтение значений из файла
with open('C:/Users/Aser/source/repos/ChisMethods/result1.txt', 'r') as file:
    lines = file.readlines()

# Преобразование строк в числа
values = [float(line.strip()) for line in lines]

# Создание списка номеров строк (x)
line_numbers = list(range(1, len(values) + 1))

# Построение графика
plt.figure(figsize=(8, 6))
plt.plot(line_numbers, values, linestyle='-', color='b')

# Настройка графика
plt.title('График зависимости погрешности от номера итерации')
plt.xlabel('N')
plt.ylabel('Loss')
plt.legend()
plt.grid(True)

# Показать график
plt.show()
