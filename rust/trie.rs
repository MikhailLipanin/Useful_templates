use std::collections::HashMap;

struct Trie {
    is_end: bool,
    nodes: HashMap<char, Trie>,
}

impl Trie {
    fn new() -> Trie {
        Trie {
            is_end: false,
            nodes: HashMap::new(),
        }
    }

    fn insert(&mut self, word: &str) {
        let mut current = self;
        for c in word.chars() {
            current = current.nodes.entry(c).or_insert(Trie::new());
        }
        current.is_end = true;
    }

    fn search(&self, word: &str) -> bool {
        let mut current = self;
        for c in word.chars() {
            if let Some(node) = current.nodes.get(&c) {
                current = node;
            } else {
                return false;
            }
        }
        current.is_end
    }
}

fn main() {
    let mut trie = Trie::new();
    trie.insert("hello");
    trie.insert("world");
    println!("{}", trie.search("hello")); // Output: true
    println!("{}", trie.search("world")); // Output: true
    println!("{}", trie.search("hi")); // Output: false
}
