#!/usr/bin/env bash
set -euo pipefail

cd /opt/BitNet

EXPECTED_FRAGMENT="Falcon3-10B-Instruct-1.58bit"

if [[ -n "${BITNET_MODEL:-}" ]]; then
    MODEL="${BITNET_MODEL}"
elif [[ -s /opt/BitNet/FALCON_MODEL_PATH ]]; then
    MODEL="$(cat /opt/BitNet/FALCON_MODEL_PATH)"
else
    MODEL="$(find /opt/BitNet/models -type f \
      -path "*${EXPECTED_FRAGMENT}*" \
      -name 'ggml-model-i2_s.gguf' -print -quit)"
fi

if [[ -z "${MODEL:-}" || ! -s "$MODEL" ]]; then
    echo "ERROR: Falcon3-10B I2_S GGUF not found." >&2
    exit 1
fi

case "$MODEL" in
    *"$EXPECTED_FRAGMENT"*) ;;
    *)
        echo "ERROR: refusing to start unexpected model: $MODEL" >&2
        exit 1
        ;;
esac

echo "=== Rebuntu BitNet Falcon3-10B semantic provider ==="
echo "Model:   $MODEL"
echo "Threads: ${BITNET_THREADS}"
echo "Context: ${BITNET_CTX}"
echo "Listen:  0.0.0.0:${BITNET_PORT}"

exec python run_inference_server.py \
    -m "$MODEL" \
    -t "${BITNET_THREADS}" \
    -c "${BITNET_CTX}" \
    --host 0.0.0.0 \
    --port "${BITNET_PORT}"
