package main

import (
    "fmt"
    "reflect"
    "./sort"
)

func main() {

    arr := sort.IntArray{1,3,2,4,6,5,0,-111,0,2,1}
    //arr := sort.IntArray{1}
    //arr := sort.IntArray{}
    fmt.Println(reflect.TypeOf(arr))
    fmt.Println(arr)
    sort.Sort(arr)
    fmt.Println(sort.IsSorted(arr))
    fmt.Println(arr)

    arrString := sort.StringArray{"monday", "friday", "tuesday", "wednesday", "sunday", "thursday", "AAA", "saturday", "zz", "ysa", " "}
    fmt.Println(arrString)
    sort.Sort(arrString)
    fmt.Println(arrString)
}
