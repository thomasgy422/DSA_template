package main


import "math/bits"

func bitLength(x uint) int {
    return bits.Len(x)
}