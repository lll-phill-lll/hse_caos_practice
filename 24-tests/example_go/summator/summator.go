package summator

// Функция для подсчета суммы элементов в массиве
func Sum(numbers []int) int {
	sum := 0
	for _, num := range numbers {
		sum += num
	}
	return sum
}

