package main


import (
    "fmt"
    "./pack1" //　自定义包路径，目录对应包名
)


func main() {
    testStr := pack1.ReturnStr2()
    fmt.Println(testStr)

    fmt.Println(pack1.PackInt)
    fmt.Println(pack1.PackInt2)
    fmt.Println(pack1.PackFloat2)
   // fmt.Println(pack1.localString)
}
