package main

import (
	"./pack1" //　自定义包路径，目录对应包名
	// 调试时方便使用上相对路径导入包ok
	// 正式部署建议使用如下，不要使用相对路径，直接导入
	// 并且把projiect放置于 $GOPATH/src 目录下
	//"pack1"
	//"xx/pack2"
	"fmt"
)

func main() {
	testStr := pack1.ReturnStr2()
	fmt.Println(testStr)

	fmt.Println(pack1.PackInt)
	fmt.Println(pack1.PackInt2)
	fmt.Println(pack1.PackFloat2)
	// fmt.Println(pack1.localString)
}
