from fastapi import FastAPI

app = FastAPI()

@app.get("/")
async def read_root():
    return {"message": "¡Servidor FastAPI corriendo con Python 3.10!"}

