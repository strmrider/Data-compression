# Data-compression

Data compression C++ library, based on Huffman coding . Encode/decode data including files.

Includes implementation of hash table, heap and huffman tree.

## Compression and decompression examples:

```
#include "compression.h"
using namespace compression;

// compress data to file
compress("YOUR_DATA", "TARGET_FILE_PATH");

// compress file
compressFile("SOURCE_FILE_PATH", "TARGET_FILE_PATH");

// decompress data to file
decompress("YOUR_DATA", "TARGET_FILE_PATH");

// decompress file
decompressFile("SOURCE_FILE_PATH", "TARGET_FILE_PATH");

// decompress file and returns the data
string data = decompress("SOURCE_FILE_PATH");

// text compression/decompression
string encodedText = encode("YOUR_DATA]);
string decodedText = decode(encodedText);
```
