# Tiny Search Engine
## Eddie Bae (GitHub username: 20eddibae)
This repository implements the three components of CS50’s Tiny Search Engine:
1. **crawler** — web crawler that pulls pages from a seed URL  
2. **indexer** — builds an inverted index from the crawled pages  
3. **querier** — answers search queries against the index  

---

## Prerequisites

- A UNIX‐compatible shell (macOS / Linux)
- `make`, `gcc`, standard build tools
- Internet connection (for crawling)

---

## Build

From the top‐level directory:

```bash
# build libcs50 and all three tools
make all
```

## Usage
1. Crawl
```bash
# <pagedir> must not exist or be empty
./crawler/crawler <seedURL> <pagedir> <maxDepth>
```

2. Indexer
```bash
mkdir indexdir
./indexer/indexer pages indexdir
```
Example: 
```bash
./crawler/crawler http://cs50tse.cs.dartmouth.edu/tse/letters pages 2
```
3. Querier
```bash
./querier/querier indexdir
```

4. Clean
```bash
make clean
```
