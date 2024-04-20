package main

import (
	"fmt"
	"project/averegator"
)

func main() {
	numbers := []int{1, 2, 3, 4, 5}

	fmt.Printf("Среднее значение чисел %v равно %.2f\n", numbers, averegator.Average(numbers))
}

