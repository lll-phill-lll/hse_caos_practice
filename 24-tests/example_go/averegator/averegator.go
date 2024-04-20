package averegator

import (
	"project/summator"
)

// Функция для подсчета среднего значения элементов в массиве
func Average(numbers []int) float64 {
	sum := summator.Sum(numbers)
	return float64(sum) / float64(len(numbers))
}
