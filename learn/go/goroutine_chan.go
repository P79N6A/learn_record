//
package main
import (
    "log"
)

func main() {
    log.Println("Start")
    ch := make(chan string)
    done := make(chan int)

    go func() {
        log.Println("Wait msg")
        str := <-ch
        log.Println(str)
        done <- 1
    }()

    go func() {
        log.Println("Send msg")
        ch <- "Hello"
    }()

    <-done
    log.Println("end")
}
