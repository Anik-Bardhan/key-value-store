# kvstore

A fast, in-memory key-value store with an interactive CLI.

## Quick Start

```bash
make        # build
./kvcli     # launch the CLI
```

## CLI Commands

| Command | Description |
|---|---|
| `set <key> <value>` | Store a value |
| `get <key>` | Retrieve a value |
| `del <key>` | Delete a key |
| `keys` | List all keys |
| `size` | Show number of stored keys |
| `quit` | Exit the CLI |

**Example session:**

```
> set name alice
> get name
alice
> keys
name
> size
1
> del name
> quit
```

## Build

```bash
make        # build kvcli
make test   # run unit tests
make clean  # remove build artifacts
```

## Design Notes

- Supports 10,000+ keys
- ASan-clean — no memory leaks or errors