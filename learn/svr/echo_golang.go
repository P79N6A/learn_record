package main

import (
	"log"
	"net"
	"encoding/binary"
	"runtime"
	"flag"
	"sync/atomic"
	"time"
)

func main() {
	//file, e := os.OpenFile("profile", os.O_RDWR|os.O_CREATE, 0666)
	//if e != nil {
	//	log.Fatal(e.Error())
	//}
	//pprof.StartCPUProfile(file)
	runtime.GOMAXPROCS(runtime.NumCPU())
	server := flag.String("ip", "127.0.0.1:9988", "ip:port")
	flag.Parse()
	ln, err := net.Listen("tcp", *server)
	if err != nil {
		log.Println(err)
		return
	}
	var totalNum int64
	go func() {
		var beforeTime int64
		ticker := time.NewTicker(time.Second * 10)
		for c := range ticker.C {
			val := atomic.LoadInt64(&totalNum)
			if val < 0{
				log.Println("atomic count err")
			}
			nowTime := val - beforeTime
			beforeTime = val
			log.Println(c.String(), nowTime)
			log.Println("avg:", nowTime/10)
			//if nowTime == 0 {
			//	pprof.StopCPUProfile()
			//}
		}
	}()

	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go echoFunc(conn, &totalNum)
	}
}


func echoFunc(c net.Conn, total *int64) {
	totalNum := 0
	tempBuf := make([]byte, 0)
	buf := make([]byte, 1024)
	//conn := c.(*net.TCPConn)
	//conn.SetReadBuffer(17)
	for {
		n, err := c.Read(buf)
		if err != nil {
			log.Println(err)
			log.Println(totalNum)
			c.Close()
			break
		}

		if n == 0 {
			continue
		}

		hasRecv := 0
		tempBufLen := len(tempBuf)
		//log.Println("tempBuf len ", len(tempBuf))
		totalLen := tempBufLen + n
		if tempBufLen != 0 {
			buf = append(tempBuf, buf[:n]...)
		}
		for {
			//log.Println("has recv:", hasRecv, "tempBufLen:", tempBufLen, "recv total:", n, "totalNum:", totalNum)
			if hasRecv+4 > totalLen {
				//log.Println("len header not enough bytes")
				tempBuf = make([]byte, totalLen-hasRecv)
				copy(tempBuf, buf[hasRecv:totalLen])
				break
			}

			dataLen := BytesToInt(buf[hasRecv:hasRecv+4])
			//log.Println("dataLen:", dataLen)

			if hasRecv+dataLen > totalLen {
				//log.Println("total data not enough bytes")
				tempBuf = make([]byte, totalLen-hasRecv)
				copy(tempBuf, buf[hasRecv:totalLen])
				break
			}

			start := hasRecv
			end := hasRecv + dataLen
			totalNum ++
			atomic.AddInt64(total, 1)
			//log.Println(string(buf[start+4:end]))
			_, err := c.Write(buf[start:end])
			if err != nil {
				log.Println(err.Error())
			}

			//attr.AttrAPI(3130908,1)

			hasRecv += dataLen
			if hasRecv == totalLen {
				//log.Println("break recv:",recv,"length:",length)
				tempBuf = make([]byte, 0)
				break
			}
		}
	}
}

//字节转换成整形
func BytesToInt(b []byte) int {
	//bytesBuffer := bytes.NewBuffer(b)
	//var x int32
	//binary.Read(bytesBuffer, binary.BigEndian, &x)
	//return int(x)
	return int(binary.BigEndian.Uint32(b))
}
