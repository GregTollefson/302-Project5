# Design Decisions

## Internal Structure

The hash table is implemented using a `std::vector` of `std::list<std::pair<K, V>>`.

- The `std::vector` provides a fixed-size array of buckets.
- Each bucket is implemented as a `std::list` to support separate chaining for collision resolution.
- Each entry stores a `(key, value)` pair, where the value represents the word frequency.

This design was chosen because:

- `std::vector` provides efficient O(1) indexing for bucket access.
- `std::list` allows efficient insertion without reallocations and supports dynamic chain growth.
- Using STL containers eliminates the need for manual memory management.

As a result, no explicit destructor logic is required, since both `std::vector` and `std::list` automatically manage their memory.

---

## Prime Table Size

The table size was set to **19997**, a prime number.

Prime table sizes help ensure that hash values are distributed more evenly across buckets. When non-prime sizes are used (e.g., 20000), certain patterns in hash values can cause some buckets to never be used, increasing clustering in others.


A prime table size ensures that all bucket indices are reachable and helps prevent systematic clustering caused by common factors between hash values and the table size.  This reduces the likelihood of clustering and improves the overall distribution of keys across

Avoiding clustering is important because when many keys are placed in the same bucket, lookups degrade from O(1) average time to O(n) time within that bucket.

---

## Finding a Real Collision

A bucket from the `modHash` table with multiple entries was examined. The words in this bucket had different spellings but produced the same ASCII sum when their characters were added together.

This occurs because `modHash` computes the hash by summing ASCII values, which is a commutative operation. As a result, words with the same letters in different orders (such as anagrams) or different combinations of characters that sum to the same value will collide.

When these same words were examined using `hornerHash`, they were placed into different buckets. This confirms that `hornerHash`, which accounts for character position, reduces collisions compared to `modHash`.

---

## Hash Function Comparison

Both hash tables were built using the same dataset and table size, resulting in identical load factors:

- Load factor: **0.375806**

However, the distribution of keys across buckets differed significantly.

### modHash

- Longest chain: **33**
- Average chain length: **5.95**

### hornerHash

- Longest chain: **5**
- Average chain length: **1.20**

The key difference between the two functions is that `modHash` ignores character position, while `hornerHash` incorporates it using polynomial hashing.

Because `modHash` only sums ASCII values, it causes many unrelated words to collide, especially those with similar character compositions. This leads to clustering, where some buckets contain many entries while others remain sparse.

In contrast, `hornerHash` evaluates the string as a polynomial, making the position of each character significant. This results in a more uniform distribution of keys across buckets.

The impact on performance is significant:

- In `modHash`, the worst-case lookup requires scanning up to **33 elements**, approaching linear time.
- In `hornerHash`, the worst-case lookup is limited to **5 elements**, maintaining near constant-time performance.

The average chain length further supports this:

- `modHash` requires approximately 6 comparisons per lookup on average.
- `hornerHash` requires only about 1.2 comparisons.

Since both tables have the same load factor, this difference is entirely due to the quality of the hash function. `hornerHash` produces a more even distribution and therefore better performance.

---

## Interesting Observations

- The most frequent words (e.g., "the", "of", "a") are common English stop words, which dominate the dataset regardless of hashing method.
- The top and bottom word frequency lists were identical for both hash functions, confirming that both tables store the same data correctly.
- The dramatic difference in chain lengths highlights how critical the choice of hash function is, even when all other factors are identical.
- No explicit memory management was required in the implementation, since `std::vector` and `std::list` automatically handle allocation and deallocation.




