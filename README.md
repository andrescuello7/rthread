# rthread

**rthread** is a simple multi-threaded C program that launches a given runtime (like `npm` or `uvicorn`) for a target application file using POSIX threads and process forking.

## Features

- Launches a subprocess using a thread per process.
- Accepts CLI arguments to configure runtime, file path, and port.
- Automatically converts Python file paths to ASGI module format for `uvicorn`.

## Usage

### Compile

```bash
gcc main.c -o rthread -lpthread
```

### Run

```bash
./rthread -m [NPM|UVICORN] -r [ROOT(main.py)] -p [PORT]
```

### Example

```bash
./rthread -m uvicorn -r samples/fastapi/app.py -p 8080
```

This will run:

```bash
uvicorn samples.fastapi.app:app
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
