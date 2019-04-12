package pack1

import (
    "fmt"
)

var PackInt2 int = 42
var PackFloat2 = 0.0

func init() {
    fmt.Println("init pack1-2")
    PackFloat2 = PackFloat
}

func ReturnStr2() string {

    fmt.Println(ReturnStr())
    fmt.Println(localString)

    return "Hello, iam pack12"
}
