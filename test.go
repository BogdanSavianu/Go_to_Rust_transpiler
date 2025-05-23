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
	return b
}

func main() {
}
