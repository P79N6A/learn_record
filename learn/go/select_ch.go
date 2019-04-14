package main

import (
	"log"
)

func main() {

// 实现退出通知机制 close chan
	var done = make(chan struct{})
    // 不阻塞无消息通道，不会进入接收case
	for i := 3; i > 0; i-- {
		select {
		case <-done:
			log.Println("rev done")
		default:
			log.Println("select default")
		}
	}
	log.Println("---------")
    // select 关闭的cha 立即返回
	close(done)
	for i := 3; i > 0; i-- {
		select {
		case <-done:
			log.Println("rev done")
		default:
			log.Println("select default")
		}
	}

}
