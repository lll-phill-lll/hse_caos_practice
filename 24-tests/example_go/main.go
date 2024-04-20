package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"project/averegator"
)

// Функция для преобразования аргументов командной строки в целочисленный формат
func convertArgsToInt(args []string) ([]int, error) {
    var numbers []int
    for _, arg := range args {
        num, err := strconv.Atoi(arg)
        if err != nil {
            return nil, err
        }
        numbers = append(numbers, num)
    }
    return numbers, nil
}

func main() {
	// Получаем аргументы командной строки
	args := os.Args[1:]

	// Преобразуем аргументы в целочисленный формат
	numbers, err := convertArgsToInt(args)
	if err != nil {
		log.Fatalf("Ошибка при преобразовании аргументов в числа: %v", err)
	}

	// Выводим числа и среднее значение
	fmt.Printf("Числа: %v\n", numbers)
	fmt.Printf("Среднее значение: %.2f\n", averegator.Average(numbers))
}

