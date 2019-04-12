//panic-recover
package main

import (
    "fmt"
)

func badCall() {
    panic("bad end")
}

func test() {

    defer func() {
        if e := recover(); e != nil {
            fmt.Println("Panicing ", e)
        }
    }()

    fmt.Println("before badcall")

    badCall()
    // will not reach here

    fmt.Println("after badcall")
}

func main() {
    fmt.Println("Start")
    test()
    fmt.Println("completed")
}
