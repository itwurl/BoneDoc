FROM ubuntu:20.04

# Umgebungsvariablen setzen, damit apt-get nicht interaktiv ist
ENV DEBIAN_FRONTEND=noninteractive

# Aktualisiere die Paketliste und installiere erforderliche Pakete
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    libboost-all-dev \
    libvtk7-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/alexander-wurl/BoneDoc.git /workdir/BoneDoc
WORKDIR /workdir/BoneDoc

RUN cmake .
RUN make

CMD ["./BoneDoc"]

