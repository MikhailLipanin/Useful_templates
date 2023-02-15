package main

import (
	"fmt"
)

type Trie struct {
	isEnd bool
	nodes map[rune]*Trie
}

func NewTrie() *Trie {
	return &Trie{nodes: make(map[rune]*Trie)}
}

func (t *Trie) Insert(word string) {
	current := t
	for _, c := range word {
		if current.nodes[c] == nil {
			current.nodes[c] = NewTrie()
		}
		current = current.nodes[c]
	}
	current.isEnd = true
}

func (t *Trie) Search(word string) bool {
	current := t
	for _, c := range word {
		if current.nodes[c] == nil {
			return false
		}
		current = current.nodes[c]
	}
	return current.isEnd
}

func main() {
	t := NewTrie()
	t.Insert("hello")
	t.Insert("world")
	fmt.Println(t.Search("hello")) // Output: true
	fmt.Println(t.Search("world")) // Output: true
	fmt.Println(t.Search("hi")) // Output: false
}
