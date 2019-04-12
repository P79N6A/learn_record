// go 实现方法
package main

import (
    "fmt"
    "strconv"
)

type MyStruct struct {
// a b 小写，并未导出，其他包不能直接用
    a int
    b int
    string //anonymous field
}

type MyStruct1 struct {
    MyStruct
    a int
}
// 匿名内嵌效果等于继承，外层类型直接使用内嵌类型的字段和方法
// 外层可以覆写字段和方法

func main() {

    struct0 := new(MyStruct1)
    struct0.a = 10
    fmt.Printf("anonymous field, struct0.a = %d\n",struct0.a )

    // struct1 is a pointer
    struct1 := new(MyStruct)
    struct1.a = 1
    struct1.b = 2
    struct1.string = "inside"
    fmt.Println("get string : ", struct1.string)

    fmt.Printf("AddTtem : %d\n", struct1.AddItem())
    fmt.Printf("AddToParam : %d\n", struct1.AddToParam(5))

    struct1.SetItemA(3)
    fmt.Println(struct1.a)
    struct1.SetItemAPretend(6)
    fmt.Println(struct1.a)

    // strcut2 is a value
    struct2 := MyStruct{3, 4, "inside"}
    fmt.Printf("AddTtem : %d\n", struct2.AddItem())
    fmt.Printf("AddToParam : %d\n", struct2.AddToParam(5))
    fmt.Println(struct2.String())
}


//类型和作用在它上面定义的方法必须在同一个包里定义

// 接收者指针，method　才能改变调用变量的值
func (this *MyStruct) SetItemA(newA int) {
    this.a = newA
}
//　传递的是一个拷贝....
func (st MyStruct) SetItemAPretend(newA int) {
    st.a = newA
}

func (this *MyStruct) AddItem() int {
    return this.a + this.b
}

func (this *MyStruct) AddToParam(param int) int {
    return this.a + this.b + param
}

func (this *MyStruct) String() string {
    return "(" + strconv.Itoa(this.a) + ", " +  strconv.Itoa(this.b) + ", " + this.string  + ")"
}
