//
package main

import (
    "fmt"
    "os"
    "bufio"
    "strings"
)

var nrchars, nrwords, nrlines = 0, 0, 0

func main() {
    inputReade := bufio.NewReader(os.Stdin)

    fmt.Println("Please input your char, end by 'S'")
    for {
        input, err := inputReade.ReadString('\n')
        if err != nil {
            fmt.Println("Err : ", err)
        } else {
            if input == "S\n" {
                fmt.Println(nrchars, nrwords, nrlines)
                break
            }
            counters(input)
        }
    }
}

func counters(input string) {
    nrchars += len(input) - 1 // \n
    nrwords += len(strings.Fields(input))
    nrlines++
}
