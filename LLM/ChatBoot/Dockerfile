FROM ubuntu:22.04
RUN echo 'APT::Install-Suggests  0 ;' >> /etc/apt/apt.conf.d/00-docker
RUN echo 'APT::Install-Recommends  0 ;' >> /etc/apt/apt.conf.d/00-docker
RUN DEBIAN_FRONTEND=noninteractive \
  apt-get update \
  && apt-get install python3 python3-pip pipx libssl-dev openssl wget g++ cmake make zlib1g-dev git vim curl sudo libsqlite3-dev -y \
  && rm -rf /var/lib/apt/lists/*
RUN useradd -ms /bin/bash apprunner

COPY key.json /tmp/key.json

# WORKDIR /tmp
# RUN wget --no-check-certificate https://www.python.org/ftp/python/3.12.0/Python-3.12.0.tgz
# RUN tar xzvf Python-3.12.0.tgz
# WORKDIR /tmp/Python-3.12.0
# RUN echo  $PWD 
# RUN ./configure
# RUN make
# RUN make install

RUN pip3 install  langchain-openai==0.1.8   \
                  langchain==0.2.1   \
                  langchain-community==0.2.1   \
                  langchain-anthropic==0.1.15  \
                  langchain-google-genai==1.0.5  \
                  langchain-google-firestore==0.3.0  \
                  firestore==0.0.8   \
                  chromadb==0.5.0  \
                  tiktoken==0.7.0  \
                  sentence-transformers==3.0.0   \
                  bs4==0.0.2   \
                  firecrawl-py==0.0.13   \
                  langchainhub==0.1.18   \
                  wikipedia==1.4.0   \
                  tavily-python==0.3.3  \
                  db-sqlite3

# WORKDIR /tmp
# RUN curl -O https://dl.google.com/dl/cloudsdk/channels/rapid/downloads/google-cloud-cli-linux-arm.tar.gz
# RUN tar -xf google-cloud-cli-linux-arm.tar.gz
# RUN ./google-cloud-sdk/install.sh
# RUN ./google-cloud-sdk/bin/gcloud init --no-launch-browser

# WORKDIR /tmp
# RUN git clone https://github.com/bhancockio/langchain-crash-course
# WORKDIR /tmp/langchain-crash-course


USER apprunner
