package main

import (
    "fmt"
    "reflect"
)

type Shaper interface {
    Area() float32
}

type Square struct {
    side float32
}
// 接口实现
func (sq *Square) Area() float32 {
    fmt.Println("square area")
    return sq.side * sq.side
}

type Rectangle struct {
    length, width float32
}
func (r *Rectangle) Area() float32 {
    fmt.Println("rectangle area")
    return r.length * r.width
}

func main() {
    q := &Square{4} // 指针，new(xx)
    r := Rectangle{5,3} //值

    fmt.Println("q type : ", reflect.TypeOf(q))
    fmt.Println("r type : ", reflect.TypeOf(r))

    var areaIntf Shaper = q
    areaIntf.Area()
    areaIntf = &r
    // 对应接口实现的接收者类型
    // 直接赋值r,接口实现接收者需要改为值传
    areaIntf.Area()
    // 判断接口变量保存值是否正确
    if u, ok := areaIntf.(*Rectangle); ok {
        fmt.Println("ok", u)
    } else {
        fmt.Println("error")
    }


    shapes := []Shaper{&r, q}
    fmt.Println("shapes type : ", reflect.TypeOf(shapes))

    for n,_ := range shapes {
        fmt.Println(shapes[n])
        fmt.Println(shapes[n].Area())
    }
}

