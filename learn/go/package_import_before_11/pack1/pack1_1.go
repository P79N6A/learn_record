// 自定义包，对应目录名
package pack1

import (
    "fmt"
)

// PackInt 全局
var PackInt int = 42
var PackFloat = 3.14

var localString = "call package local"

func init() {
    fmt.Println("init pack1-1")
}

func ReturnStr() string {
    return "Hello, iam pack1-1"
}
