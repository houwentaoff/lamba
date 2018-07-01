package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time"
)

func test_anonymous(t int) {
	time.Sleep(time.Duration(t) * time.Second)
	fmt.Println("exec ", t)
}

func main() {
	sem := make(chan int, 1)

	go test_anonymous(2)
	go func(t int) {
		//do work
		time.Sleep(time.Duration(t) * time.Second)
		fmt.Println("exec ", t)
		sem <- 1
	}(3)

	<-sem
	fmt.Println("exec 3 is test over!")
	sigChan := make(chan os.Signal)
	signal.Notify(sigChan, os.Interrupt, syscall.SIGTERM)
	fmt.Println("signal", <-sigChan)
}
