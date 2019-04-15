package main

// XXXXimport "package_import_after_11"

/* 在package main 后面注释  -> // import "projectname"
然后执行 go mod init 生成 go.mod
或者不加注释，直接执行 go mod init projectname

之后，工程下自定义包导入按如下格式 "projectname/packname"
*/
import (
	"fmt"
	"github.com/robteix/testmod"
	"package_import_after_11/pack1"
)

func main() {
	testStr := pack1.ReturnStr2()
	fmt.Println(testStr)

	fmt.Println(pack1.PackInt)
	fmt.Println(pack1.PackInt2)
	fmt.Println(pack1.PackFloat2)
	// fmt.Println(pack1.localString)
	fmt.Println(testmod.Hi("Testmod"))
}
