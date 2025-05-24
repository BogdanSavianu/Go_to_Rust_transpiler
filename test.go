package main

import "fmt"

func do_something(c int) int {
	a := 10
	b := a + 5
	if 2 < 10 {
		b = b + 3
	} else {
		b = b - 3
	}

	while b < 30 {
		b = b + 1
	}

	for i := 0; i < a; i = i + 1 {
		b = b + i
		if i % 2 == 0 {
			b = b * 2
		}
	}

	return b
}

func main() {
}
