# PHP UUID Extension

A PHP extension providing various UUID generation methods, including:

- UUID v1, v3, v4, v5, v6, v7  
- Snowflake IDs  
- KSUID (Segment.com style)  
- ULID (Crockford base32)  
- Raw 128-bit UUID binary output  

This extension is designed for high performance native UUID generation inside PHP.

## Features

- Generate standard UUID versions (v1-v7)  
- Generate Twitter-style Snowflake IDs  
- Generate KSUID and ULID identifiers  
- Generate raw 128-bit UUID binary strings  
- Thread-safe snowflake sequence generation  
- Compatible with PHP 7.4+  

## Usage

Call static methods on the `uuid` class:

```php
<?php
echo uuid::v4(), "\n";          // e.g. 9b9e3a0a-9f60-42b6-91a2-c432a3ef8f68
echo uuid::v7(), "\n";          // UUIDv7 with timestamp and randomness
echo uuid::snowflake(), "\n";   // Twitter Snowflake numeric string
echo uuid::ksuid(), "\n";       // KSUID (27-character base62)
echo uuid::ulid(), "\n";        // ULID (26-character base32)
echo uuid::uuid128(), "\n";     // Raw 16-byte binary string
?>
```

## Building and Installing Using Docker
You can build and test the extension inside a Docker container. 

To build and install the extension on your local PHP installation, use the Docker container as a build environment, then copy the resulting .so file to your PHP extensions directory.

### Build Docker Image
```bash
git clone https://github.com/richvigorito/php-uuid-extension.git
cd php-uuid-extension

docker build -t php-uuid-extension .
```

### Run Tests Inside Container
```bash 
docker run --rm php-uuid-extension make test
```
## Development Notes
- Requires libuuid development headers (uuid/uuid.h) for some UUID implementations.
- Snowflake implementation uses pthread mutex for thread safety.
- Uses getentropy() for cryptographic randomness.
- Compatible with PHP 7.4 and later.

Credits
Dockerfile structure and build approach inspired by [php extension hellow word](bogkonstantin/php-extension-hello-world)

UUID generation algorithms adapted and implemented based on relevant specifications and public resources.
