FROM arm64v8/ubuntu:22.04

ARG AWS_ACCESS_KEY
ARG AWS_SECRET_KEY
ARG USER
ENV AWS_ACCESS_KEY=$AWS_ACCESS_KEY
ENV AWS_SECRET_KEY=$AWS_SECRET_KEY
ENV USER=$USER

RUN apt-get update && \
    apt-get install -y --no-install-recommends python3-pip ssh && \
    rm -rf "/var/lib/apt/lists/*" && \
	pip3 install --no-cache-dir ansible==5.0.1 && \
	ansible-galaxy collection install community.aws && \
	pip3 install --no-cache-dir -r "$HOME/.ansible/collections/ansible_collections/amazon/aws/requirements.txt"

RUN mkdir "$HOME/.ssh" && touch "$HOME/.ssh/known_hosts"
WORKDIR /app
COPY . .

CMD ["ansible-playbook playbooks/deploy.yaml --private-key $USER-key-pair.pem"]
