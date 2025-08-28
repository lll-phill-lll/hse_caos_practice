package main

import (
	"os/exec"
	"strings"
	"testing"
)

func TestMain(t *testing.T) {
	tests := []struct {
		name          string
		args          []string
		expected      string
		expectedError bool
	}{
		{"NoArguments", []string{}, "Использование: ./main число1 число2 число3 ...", false},
        {"ValidArguments", []string{"1", "2", "3", "4", "5"}, "Числа: [1 2 3 4 5]\nСреднее значение: 3.00", false},
		{"InvalidArguments", []string{"1", "2", "abc", "4", "5"}, "", true},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			cmd := exec.Command("go", "run", "main.go")
			cmd.Args = append(cmd.Args, test.args...)
			output, err := cmd.CombinedOutput()

			if test.expectedError && err == nil {
				t.Errorf("Ожидалась ошибка, но она не возникла")
			}

			if !test.expectedError && err != nil {
				t.Errorf("Произошла неожиданная ошибка: %v", err)
			}

			actual := strings.TrimSpace(string(output))
			if actual != test.expected {
				t.Errorf("Неправильный вывод. Ожидалось: '%s', получено: '%s'", test.expected, actual)
			}
		})
	}
}

