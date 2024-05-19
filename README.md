# LRUCache Implementation

## Overview

This project implements a Least Recently Used (LRU) cache with time expiration. The cache supports multiple data types, and it handles cache evictions based on both capacity limits and expiration times.

## Installation and Usage

### Prerequisites

- C++ compiler (GCC, Clang, etc.)
- C++11 or later

### Building the Project

1. Clone the repository:

```sh
git clone https://github.com/ssagun/TechTest.git
cd TechTest
```

2. Compile the code:

```sh
g++ -std=c++11 LRUCache.cpp -o LRUCache
```

### Running the Program

Execute the compiled binary:

```sh
./LRUCache
```

## Code Structure

- `LRUCache`: Template class implementing the LRU cache.
- `main()`: Demonstrates the usage of the `LRUCache` class and tests various scenarios such as cache expiration and LRU eviction.

### Main Components

1. **CacheEntry**: Stores the value, position in the LRU list, and the timestamp of the entry.
2. **put()**: Adds a new entry to the cache, evicting the least recently used entry if the capacity is exceeded.
3. **get()**: Retrieves an entry from the cache and updates its position to the most recently used.
4. **cleanExpiredEntries()**: Periodically removes expired entries from the cache.
5. **printValue()**: Prints the value stored in a cache entry.
6. **printCacheState()**: Prints the current state of the cache for debugging purposes.

## Example Usage

The `main()` function demonstrates how to use the `LRUCache`:

1. Create a cache with a capacity of 3 entries and an expiration time of 5 seconds.
2. Add entries to the cache and print its state.
3. Access entries to update their positions and print the cache state.
4. Wait for entries to expire and print the cache state.
5. Add new entries to test LRU eviction and print the cache state.

## Testing

The program includes a variety of test scenarios to ensure the LRU cache functions correctly, including:

- Adding and retrieving entries.
- Handling cache expiration.
- Evicting the least recently used entries when the capacity is exceeded.

## Future Enhancements

- Implement distributed cache functionality.
- Enhance resilience to network failures.
- Add more data types and custom expiration policies.
