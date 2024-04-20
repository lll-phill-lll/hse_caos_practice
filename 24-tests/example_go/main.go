package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"project/averegator"
)

func main() {
	// Получаем аргументы командной строки
	args := os.Args[1:]

	// Если не указаны аргументы, выводим сообщение и завершаем программу
	if len(args) == 0 {
		fmt.Println("Использование: ./main число1 число2 число3 ...")
		return
	}

	// Преобразуем аргументы в целочисленный формат
	var numbers []int
	for _, arg := range args {
		num, err := strconv.Atoi(arg)
		if err != nil {
			log.Fatalf("Ошибка при преобразовании аргумента в число: %v", err)
		}
		numbers = append(numbers, num)
	}

	// Выводим числа и среднее значение
	fmt.Printf("Числа: %v\n", numbers)
	fmt.Printf("Среднее значение: %.2f\n", averegator.Average(numbers))
}

