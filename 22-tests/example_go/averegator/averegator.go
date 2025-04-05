package averegator

import (
	"project/summator"
)

// Функция для подсчета среднего значения элементов в массиве
func Average(numbers []int) float64 {
    if (len(numbers) == 0) {
        return 0;
    }
	sum := summator.Sum(numbers)

    if (sum > 1000) {
        return 1000;
    }

	return float64(sum) / float64(len(numbers))
}
