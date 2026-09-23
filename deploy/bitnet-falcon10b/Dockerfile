FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

ENV PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1 \
    PIP_NO_CACHE_DIR=1

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates git curl build-essential cmake ninja-build \
    clang-18 llvm-18 libomp-dev python3 python3-pip python3-venv \
    && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100 \
 && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100

WORKDIR /opt
RUN git clone --recursive https://github.com/microsoft/BitNet.git

WORKDIR /opt/BitNet
RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:${PATH}"

RUN pip install --upgrade pip setuptools wheel \
 && pip install -r requirements.txt

# Download the official pre-quantized Falcon3-10B I2_S GGUF directly.
RUN huggingface-cli download tiiuae/Falcon3-10B-Instruct-1.58bit-GGUF ggml-model-i2_s.gguf \
      --local-dir models/Falcon3-10B-Instruct-1.58bit \
 && test -s models/Falcon3-10B-Instruct-1.58bit/ggml-model-i2_s.gguf \
 && python setup_env.py \
      -md models/Falcon3-10B-Instruct-1.58bit \
      -q i2_s \
 && printf "%s\n" "/opt/BitNet/models/Falcon3-10B-Instruct-1.58bit/ggml-model-i2_s.gguf" > /opt/BitNet/FALCON_MODEL_PATH


COPY entrypoint.sh /usr/local/bin/rebuntu-bitnet-falcon10b-entrypoint
RUN chmod +x /usr/local/bin/rebuntu-bitnet-falcon10b-entrypoint

ENV BITNET_THREADS="4" \
    BITNET_CTX="4096" \
    BITNET_PORT="8082"

EXPOSE 8082

ENTRYPOINT ["/usr/local/bin/rebuntu-bitnet-falcon10b-entrypoint"]
