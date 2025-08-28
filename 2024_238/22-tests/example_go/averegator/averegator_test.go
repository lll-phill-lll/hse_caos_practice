package averegator

import "testing"

func TestAverage(t *testing.T) {
	tests := []struct {
		name     string
		numbers  []int
		expected float64
	}{
		{"PositiveNumbers", []int{1, 2, 3, 4, 5}, 3},
		{"NegativeNumbers", []int{-1, -2, -3, -4, -5}, -3},
		{"MixedNumbers", []int{-1, 2, -3, 4, -5}, -0.6},
		{"Empty", []int{}, 0},
		{"1000", []int{500, 500, 500}, 1000},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			result := Average(test.numbers)
			if result != test.expected {
				t.Errorf("Ожидается среднее значение %.2f, получено %.2f", test.expected, result)
			}
		})
	}
}

