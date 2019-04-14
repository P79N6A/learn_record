//
package main

import (
	"flag"
	"fmt"
	"os"
	"strings"
)


var port *int = flag.Int("port", 1000, "server port")
var ip *string = flag.String("ip", "127.0.0.1", "server ip")

func main() {
	var str string
	str = strings.Join(os.Args[1:], " ")
	fmt.Println(str)

	flag.Parse()
    fmt.Println(*ip, " : ", *port)
}
