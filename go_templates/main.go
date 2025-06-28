package main

import (
	"bufio"
	. "fmt"
	"io"
	"os"
	"strings"
)

func run(in io.Reader, _w io.Writer) {
	out := bufio.NewWriter(_w)
	defer out.Flush()

	solve := func(curCase int) (_res bool) {
		var n int
		Fscan(in, &n)

		return
	}

	cases := 1
	Fscan(in, &cases)
	for curCase := range cases {
		ans := solve(curCase + 1)
		_ = ans

	}

	leftData, _ := io.ReadAll(in)
	if s := strings.TrimSpace(string(leftData)); s != "" {
		panic("There is unread input data:\n" + s)
	}

}

func main() { run(bufio.NewReader(os.Stdin), os.Stdout) }
