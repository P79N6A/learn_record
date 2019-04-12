package main

import (
	"fmt"
    "runtime"
    "strconv"
    "reflect"
)

// Pi  const value
const Pi = 3.14159
const beef, two, veg = "eat", 2, "veg"

// iota is ..
const (
    a = iota
    b
    c
)

const (
    d = iota
)


// init will called after imported, before main run
func init() {
    fmt.Println("call init")
}

func condition(booValue bool) (boolReturn bool, a int) {

    defer func() {
        fmt.Println("defer1 get inout value ", booValue, boolReturn, a)
    }()
    // 参数在调用时传入确定了
    defer fmt.Println("defer2 get inout value ", booValue, boolReturn, a)

    if booValue {
        return false, 1
    }
    return true, 2
}


// main is ...
func main() {
    fmt.Println("Go version: ", runtime.Version())
    fmt.Printf("%f\n", Pi)
    fmt.Printf("a=%d, b=%d, c=%d, d=%d\n", a, b ,c, d)

    var valueOne int = 1
    valueTemp := valueOne // 简短初始化声明
    valueTemp = 2
    fmt.Printf("one=%d, tmp=%d\n", valueOne, valueTemp)

    bool1 := false
    if bool1 {
        fmt.Println("bool1 is true")
    } else {
        fmt.Println("bool1 is false")
    }

    bool2, a := condition(bool1)
    fmt.Println(bool2, a)
    if b := 1; a == b {
        fmt.Println("a == b")
    }

    if runtime.GOOS == "windows" {
        fmt.Println("iamwindows")
    } else if runtime.GOOS == "linux" {
        fmt.Println("iamlinux")
    } else {
        fmt.Println("iamfruit")
    }

    var origString string = "ABC"
    var newString  string
    an, err := strconv.Atoi(origString)
    if err != nil {
        fmt.Printf("origString is not a integer, err:  %s\n", err)
    } else {
        fmt.Printf("originString is %d", an)
        newString = strconv.Itoa(an)
        fmt.Printf("newstring is %s\n", newString)
    }

    i := "pear"
    switch i {
    case "apple":
        fmt.Println("apple")
    case "pear", "banana":
        fmt.Println("pb")
        fallthrough // 继续下面case
    default:
        fmt.Println("default")
    }

    switch {
    case i == "apple":
        fmt.Println("is apple")
    case i == "pear":
        fmt.Println("is pear")
    default:
        fmt.Println("swith default")
    }

    var arr1 [5]int
    for i:=1;i < len(arr1); i++ {
        arr1[i] = i * 2
    }
    for i, v := range arr1 {
        fmt.Printf("arr1[%d] = %d, ", i, v)
    }
    fmt.Println("")

    //// slice
    var arr2 [5]int = arr1
    var slice1 []int = arr1[:] // no len
    arr1[1] = 100
    slice1[2] = 200
    for i, v := range arr1 {
        fmt.Printf("arr1[%d] = %d, ", i, v)
    }
    fmt.Println("")
    for i, v := range slice1 {
        fmt.Printf("slice1[%d] = %d, ", i, v)
    }
    fmt.Println("")
    for i, v := range arr2 {
        fmt.Printf("arr2[%d] = %d, ", i, v)
    }
    fmt.Println("")

    var slice2 = []int{2,3,4,5}[1:2]
    for i, v := range slice2 {
        fmt.Printf("slice2[%d] = %d, ", i, v)
    }
    fmt.Printf("\nslice2 len : %d, capacity %d\n", len(slice2), cap(slice2))

    var slice3 []int = make([]int, 2, 5)
    for i, _ := range slice3 {
        slice3[i] = i * 10
    }
    for i, val := range slice3 {
        fmt.Printf("slice3[%d] = %d,", i, val)
    }
    fmt.Println("")
    slice3 = slice3[:cap(slice3)]
    for i, val := range slice3 {
        fmt.Printf("slice3[%d] = %d,", i, val)
    }
    fmt.Println("")

    sl_from := []int{1, 2, 3}       // slice
    //var sl_from =  []int{1, 2, 3} // array
    fmt.Println(reflect.TypeOf(sl_from))

    sl_to := make([]int, 10, 11)
    //sl_to := make([]int, 10, 15)
    n := copy(sl_to, sl_from)
    fmt.Println(sl_to)
    fmt.Printf("copy elemets %d\n", n)

    sl_to  = append(sl_to, sl_from...)
    fmt.Println(sl_to)
    sl_to = sl_to[:cap(sl_to)]
    fmt.Println(sl_to)


    /// map
    var mapList map[string]int   // 声明
    mapList = map[string]int{"one":1}//初始化
    mapList["one"] = 11
    mapList["two"] = 22
    fmt.Println(mapList)

    var mapAssigned = mapList // map 是引用类型
    mapAssigned["one"] = 111
    fmt.Println(mapList)
    fmt.Println(mapAssigned)

    var mapCreated = make(map[string]int)
    mapCreated["aa"] = 0xaa
    fmt.Println(mapCreated)

    // value as slice
    var mapArry = make(map[int][]int)
    mapArry[1] = []int{1,2,3}
    fmt.Println(mapArry)
    fmt.Println(reflect.TypeOf(mapArry[1]))

    value, isPresen := mapArry[1]
    fmt.Println(isPresen, value)
    delete(mapArry, 1)
    value, isPresen = mapArry[1]
    fmt.Println(isPresen, value)
}
