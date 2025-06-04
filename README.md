# rthread

**rthread** is a simple multi-threaded C program that launches a given runtime (like `npm` or `uvicorn`) for a target application file using POSIX threads and process forking.

## Features

- Launches a subprocess using a thread per process.
- Accepts CLI arguments to configure runtime, file path, and port.
- Automatically converts Python file paths to ASGI module format for `uvicorn`.

## Usage

### Compile

```bash
gcc main.c src/for_uvicorn.c src/process_list.c src/logs.c -o rthread \
  -Iinclude \
  -I/opt/homebrew/Cellar/cjson/1.7.18/include \
  -L/opt/homebrew/Cellar/cjson/1.7.18/lib \
  -lcjson -lpthread

```

### Run

```bash
$ rthread -m [NPM|UVICORN] -r [ROOT(main.py)] -p [PORT]
```

### Example

```bash
# Python
$ rthread -m uvicorn -r samples/fastapi/app.py -p 8080

# Node
$ rthread -m node -r samples/express/app.js -p 8080
```

## Structure

- `main.c`: Main source file
- `ThreadStruct`: Contains data for each thread
- `run_process`: Forks and executes the process in a thread
- `format_module_path`: Converts `path/to/file.py` to `path.to.file:app`

## Notes

- Currently supports only one thread/process by default (`num_threads = 1`).
- Assumes the target file is valid and accessible.
- If using `uvicorn`, make sure the path points to a valid ASGI app.

---
