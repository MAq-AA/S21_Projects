#!/bin/bash
echo " \!\"\#\$\%\&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_\`abcdefghijklmnopqrstuvwxyz{|}~ 




aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1216
" > test_file.txt


# Тест 1
expected=$(cat test_file.txt)
actual=$(./s21_cat test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Вывод без флагов не совпадает!"
else 
    echo "Успех: Правильный вывод без флагов"
fi

# Тест 2
expected=$(cat -n test_file.txt)
actual=$(./s21_cat -n test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -n!"
else 
    echo "Успех: Правильный вывод с флагом -n"
fi

# Тест 3
expected=$(cat -b test_file.txt)
actual=$(./s21_cat -b test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -b!"
else 
    echo "Успех: Правильный вывод с флагом -b"
fi

# Тест 4
expected=$(cat -s test_file.txt)
actual=$(./s21_cat -s test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -s!"
else 
    echo "Успех: Правильный вывод с флагом -s"
fi

# Тест 5
expected=$(cat -v test_file.txt)
actual=$(./s21_cat -v test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -v!"
else 
    echo "Успех: Правильный вывод с флагом -v"
fi

# Тест 6
expected=$(cat -e test_file.txt)
actual=$(./s21_cat -e test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -e!"
else 
    echo "Успех: Правильный вывод с флагом -e"
fi

# Тест 7
expected=$(cat -t test_file.txt)
actual=$(./s21_cat -t test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -t!"

else 
    echo "Успех: Правильный вывод с флагом -t"
fi

#
# GNU TESTS
#

# Тест 8
expected=$(cat -E test_file.txt)
actual=$(./s21_cat -E test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -E!"

else 
    echo "Успех: Правильный вывод с флагом -E"
fi

# Тест 9
expected=$(cat -T test_file.txt)
actual=$(./s21_cat -T test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом -T!"

else 
    echo "Успех: Правильный вывод с флагом -T"
fi

# Тест 10
expected=$(cat --number-nonblank test_file.txt)
actual=$(././s21_cat --number-nonblank test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с --number-nonblank!"

else 
    echo "Успех: Правильный вывод с --number-nonblank!"
fi

# Тест 11
expected=$(cat --number test_file.txt)
actual=$(././s21_cat --number test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с --number!"

else 
    echo "Успех: Правильный вывод с --number"
fi

# Тест 12
expected=$(cat --squeeze-blank test_file.txt)
actual=$(././s21_cat --squeeze-blank test_file.txt)
if [[ "$expected" != "$actual" ]]; then
    echo "$expected"
    echo -------------------------------------------------------------------
    echo "$actual"
    echo "Ошибка: Неправильный вывод с флагом --squeeze-blank!"

else 
    echo "Успех: Правильный вывод с флагом --squeeze-blank"
fi

rm -rf "test_file.txt"