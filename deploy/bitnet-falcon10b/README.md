# Rebuntu BitNet — Falcon3-10B

Corrected standalone Falcon3-10B BitNet container.

It deliberately uses unique Docker identities:

- image: `rebuntu-bitnet-falcon10b:local`
- container: `rebuntu-bitnet-falcon10b`
- API: `127.0.0.1:8082`

It does not delete the old BitNet container, image, or volume.

## Build

```bash
docker compose build --no-cache --progress=plain
```

The build fails if it cannot produce and verify a Falcon3-10B
`ggml-model-i2_s.gguf`. If `setup_env.py` fails, available BitNet logs are
dumped into the build output.

## Start

```bash
docker compose up -d
```

## Verify the actual loaded model

```bash
curl -s http://127.0.0.1:8082/v1/chat/completions \
  -H 'Content-Type: application/json' \
  -d '{
    "messages":[{"role":"user","content":"What is the capital of France? Answer in one sentence."}],
    "temperature":0.1,
    "max_tokens":50
  }' | jq '{model, choices, timings}'
```

The returned `model` path MUST contain:

`Falcon3-10B-Instruct-1.58bit`

If it says `BitNet-b1.58-2B-4T`, stop: that is not this image.

## Inspect

```bash
docker ps --format 'table {{.Names}}\t{{.Image}}\t{{.Ports}}\t{{.Status}}'
docker logs rebuntu-bitnet-falcon10b --tail 100
```

## Important

Do not run `docker compose down` from the old 2.4B project merely to start
this one. This project has its own image/container identity and is intended
not to destroy or overwrite the old setup.
